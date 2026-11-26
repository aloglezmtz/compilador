#!/usr/bin/env python3
"""Interfaz local del analizador. Uso: python servidor.py  ->  http://127.0.0.1:8765
Solo escucha en tu computadora (127.0.0.1). En Windows ejecuta los comandos dentro de MSYS2 UCRT64."""
import json, os, re, subprocess, time, webbrowser
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import urlparse, parse_qs

AQUI = os.path.dirname(os.path.abspath(__file__))
RAIZ = os.path.dirname(AQUI)                      # carpeta analizador_cpp
NT = os.name == "nt"
EXE = ".exe" if NT else ""
ST = "-static " if NT else ""
FIJOS = {n: n for n in ("slimc_manual.c", "lexer.l", "parser.y", "tabla_simbolos.c", "tabla_simbolos.h", "semantica.c", "semantica.h")}
PUERTO = 8765


def msys():
    for r in (os.environ.get("MSYS2_ROOT"), r"C:\msys64", r"C:\msys32"):
        if r and os.path.exists(os.path.join(r, "usr", "bin", "bash.exe")):
            return r


def ejecutar(cmd, cwd="", timeout=90):
    t0, env = time.time(), dict(os.environ)
    cwd = os.path.join(RAIZ, cwd)
    if NT:
        r = msys()
        if not r:
            return dict(ok=False, code=-1, out="No encontré MSYS2 en C:\\msys64.", ms=0, cmd=cmd)
        env.update(MSYSTEM="UCRT64", CHERE_INVOKING="1")
        args, flags = [os.path.join(r, "usr", "bin", "bash.exe"), "-lc", cmd], 0x08000000
    else:
        args, flags = ["sh", "-c", cmd], 0
    try:
        p = subprocess.run(args, cwd=cwd, env=env, capture_output=True, timeout=timeout, creationflags=flags)
        out, code = (p.stdout + p.stderr).decode("utf-8", "replace"), p.returncode
    except subprocess.TimeoutExpired:
        out, code = "Tiempo agotado.", -1
    return dict(ok=code == 0, code=code, out=out, ms=int((time.time() - t0) * 1000), cmd=cmd)


def ruta(nombre):
    if nombre in FIJOS:
        return os.path.join(RAIZ, FIJOS[nombre])
    if re.fullmatch(r"[\w\-]+\.c", nombre or ""):
        return os.path.join(RAIZ, nombre)


def pasos(a):
    srcs = "tabla_simbolos.c semantica.c"
    return {
        "g++": ("", f"gcc {ST}-Wall slimc_manual.c {srcs} -o slimc_manual{EXE}"),
        "cpp": ("", f"./slimc_manual{EXE} '{a}'"),
        "tokens": ("", f"./slimc_manual{EXE} --tokens '{a}'"),
        "bison": ("", "bison -d parser.y"),
        "flex": ("", "flex lexer.l"),
        "gcc": ("", f"gcc {ST}parser.tab.c lex.yy.c {srcs} -o slimc{EXE}"),
        "bis": ("", f"./slimc{EXE} '{a}'"),
    }


class H(BaseHTTPRequestHandler):
    def log_message(self, *a):
        pass

    def enviar(self, datos, tipo="application/json", codigo=200):
        if not isinstance(datos, bytes):
            datos = json.dumps(datos).encode()
        self.send_response(codigo)
        self.send_header("Content-Type", tipo + "; charset=utf-8")
        self.send_header("Content-Length", str(len(datos)))
        self.end_headers()
        self.wfile.write(datos)

    def do_GET(self):
        u = urlparse(self.path)
        if u.path in ("/", "/index.html"):
            return self.enviar(open(os.path.join(AQUI, "index.html"), "rb").read(), "text/html")
        if u.path == "/api/archivos":
            cs = sorted(f for f in os.listdir(RAIZ) if re.fullmatch(r"[\w\-]+\.c", f) and f not in FIJOS)
            return self.enviar(cs + list(FIJOS))
        if u.path == "/api/archivo":
            p = ruta(parse_qs(u.query).get("n", [""])[0])
            if p and os.path.exists(p):
                return self.enviar({"contenido": open(p, encoding="utf-8").read()})
            return self.enviar({"error": "No existe"}, codigo=404)
        if u.path == "/api/entorno":
            r = ejecutar("for t in g++ gcc flex bison; do command -v $t >/dev/null && echo $t=1 || echo $t=0; done", timeout=30)
            return self.enviar(dict(l.split("=") for l in r["out"].split() if "=" in l))
        self.enviar({"error": "?"}, codigo=404)

    def do_POST(self):
        if self.headers.get("X-Req") != "1":
            return self.enviar({"error": "prohibido"}, codigo=403)
        d = json.loads(self.rfile.read(int(self.headers.get("Content-Length", 0))) or b"{}")
        if self.path == "/api/guardar":
            p = ruta(d.get("nombre"))
            if not p:
                return self.enviar({"error": "Nombre no permitido"}, codigo=400)
            with open(p, "w", encoding="utf-8", newline="\n") as f:
                f.write(d.get("contenido", ""))
            return self.enviar({"ok": True})
        if self.path == "/api/paso":
            a = d.get("archivo", "prueba.c")
            if not re.fullmatch(r"[\w\-]+\.c", a):
                return self.enviar({"error": "Archivo no permitido"}, codigo=400)
            cwd, cmd = pasos(a).get(d.get("paso"), (None, None))
            if cmd is None:
                return self.enviar({"error": "Paso desconocido"}, codigo=400)
            return self.enviar(ejecutar(cmd, cwd))
        self.enviar({"error": "?"}, codigo=404)


if __name__ == "__main__":
    srv = ThreadingHTTPServer(("127.0.0.1", PUERTO), H)
    url = f"http://127.0.0.1:{PUERTO}"
    print(f"Interfaz lista en {url}  (Ctrl+C para cerrar)")
    try:
        webbrowser.open(url)
        srv.serve_forever()
    except KeyboardInterrupt:
        print("Cerrado.")
