# SlimC: analizador léxico, sintáctico y semántico (Flex + Bison)

Actividad Integradora Final, carpeta `proyecto-finalslimc`. Extiende el analizador de la clase con
operadores relacionales y lógicos, `double`, `const`, cadenas, `if/else`, `while`, recuperación de
errores y análisis semántico con tabla de símbolos.

## Archivos

| Archivo | Para qué sirve | ¿Se entrega? |
|---|---|---|
| `lexer.l` | Especificación léxica (Flex) | Sí |
| `parser.y` | Gramática, recuperación de errores y acciones (Bison) | Sí |
| `tabla_simbolos.h` / `.c` | Tabla de símbolos con pila de ámbitos | Sí |
| `semantica.h` / `.c` | Verificaciones semánticas (las llama `parser.y`) | Sí (las necesita `parser.y`) |
| `correcto.c` | Programa válido: debe dar ACCEPT | Sí |
| `errores.c` | Programa con los 7 errores semánticos del documento del profe | Sí |
| `errores_extra.c` | Extra: errores léxicos, sintácticos y semánticos mezclados | Opcional |
| `slimc_manual.c` | Versión de descenso recursivo en C (respaldo y referencia) | Opcional |
| `esperado_errores.txt`, `probar.sh` | Prueba automática de los 7 errores esperados | Opcional |
| `Makefile`, `compilar.sh`, `compilar.bat` | Compilación | Opcional |
| `interfaz/` | Interfaz local en el navegador | Opcional |

## Requisitos

- **Windows 11:** MSYS2 UCRT64. En esa terminal, una sola vez:
  `pacman -S --needed mingw-w64-ucrt-x86_64-gcc flex bison make`
- **Ubuntu/Debian:** `sudo apt install -y build-essential flex bison python3`
- Se necesita **Bison 3.0 o superior** (el de MSYS2 y Ubuntu 24.04 es 3.8.2).

## Compilar paso a paso (igual que en clase)

En la carpeta del proyecto:

```
bison -d parser.y
flex lexer.l
gcc parser.tab.c lex.yy.c tabla_simbolos.c semantica.c -o slimc
./slimc correcto.c
./slimc errores.c
```

En Windows agrega `-static` al `gcc` y el programa se llama `slimc.exe`. Atajos: `./compilar.sh`,
`make` o doble clic en `compilar.bat`. Para verificar todo de una vez: `./probar.sh`.

La versión manual se compila con:
`gcc slimc_manual.c tabla_simbolos.c semantica.c -o slimc_manual`

## Salida esperada

- `correcto.c` termina con **`✅ Programa en C válido (ACCEPT).`**, imprime la tabla de símbolos y
  los tres conteos de errores en 0.
- `errores.c` reporta, sin abortar, exactamente los 7 errores de `esperado_errores.txt`
  (líneas 3, 22, 23, 24, 25, 27 y 31) y el resumen con `Errores semánticos: 7`.

## Interfaz en el navegador

Doble clic en `interfaz/iniciar.bat` (Windows) o `./interfaz/iniciar.sh` (Linux). Se abre
`http://127.0.0.1:8765` con un editor y un botón por paso: compilar la versión manual, `bison`,
`flex`, `gcc`, ejecutar y comparar las dos versiones. Se guarda solo al presionar un paso.

## Qué cubre cada requisito

| Requisito del documento | Dónde |
|---|---|
| Relacionales `== != < > <= >=` y lógicos `&& \|\| !` | `lexer.l` y reglas de `expresion` en `parser.y` |
| Comentarios `//` y `/* */` sin alterar `yylineno` | `lexer.l` (`%option yylineno`) |
| `#include`, `#define` con literal, `const` | `lexer.l`, reglas `directiva` y `declaracion_const` |
| Varias librerías, macros (`MAX 10`, `PI 3.14`) y constantes tipadas al inicio | regla `prelude` |
| `if` e `if-else` (también `else if`) con llaves | `sentencia_if` |
| `while` | `sentencia_while` |
| Recuperación con `error` y `yyerrok` | `sentencia: error ';'` y `funcion: error '}'` |
| Protección de constantes y macros | `sem_asignar` |
| Variables y tipos en condiciones `if`/`while` | `sem_usar_variable`, `sem_condicion_fin` |
| Tipo de retorno | `sem_retorno` |
| Ámbito, aridad, tipos y redeclaración | `sem_usar_variable`, `sem_llamada`, `sem_declarar_variable`, `sem_definir_macro` |
| Tabla de símbolos y resumen final | `ts_imprimir` y `sem_resumen` |

## Reglas semánticas y decisiones de diseño

- Tipos: `int`, `double` y cadena (solo como argumento de `printf`/`scanf`, que están predefinidas).
- `int` se puede usar donde se espera `double`; un `double` donde se espera `int` es error
  (en argumentos, asignaciones, inicializaciones y `return`).
- Los bloques `{ }` abren un ámbito propio; los símbolos de ámbitos cerrados siguen apareciendo en la
  tabla final, con el nombre de su ámbito (`main.bloque1`).
- Dentro de una condición, una variable no declarada se reporta como
  «no declarada en condición 'if'» (o `'while'`).
- Las sentencias `if` y `while` exigen llaves. No se incluyó `for`: el documento pide `while` **o** `for`.
- La función `main` puede estar en cualquier posición y debe existir.

## Estado de verificación

- **Probado:** `tabla_simbolos.c`, `semantica.c` y `slimc_manual.c` se compilaron sin avisos y la
  versión manual da ACCEPT en `correcto.c` y los 7 errores exactos en `errores.c`.
- **Verificado con herramientas propias:** una revisión estática de tipos y números de símbolo de
  `parser.y`/`lexer.l`, y un generador LALR(1) que confirmó que la gramática no tiene conflictos,
  acepta `correcto.c` y `errores.c`, y rechaza, por ejemplo, un `if` sin llaves.
- **No probado:** la compilación real con `bison` y `flex`, porque el entorno donde se escribió no los
  tiene instalados. Si `./compilar.sh` muestra un error, copia el mensaje completo para corregirlo.
- El `errores.c` incluido se reconstruyó del PDF con líneas en blanco y un comentario para que los
  números de línea coincidan con los esperados; con el archivo original del profe, el analizador usa
  las líneas reales de cada token.

## Subir a GitHub

```
mkdir proyecto-finalslimc        # dentro de tu repositorio
# copiar: lexer.l parser.y tabla_simbolos.h tabla_simbolos.c semantica.h semantica.c correcto.c errores.c
git add proyecto-finalslimc
git commit -m "SlimC: analizador léxico, sintáctico y semántico"
git push
```
