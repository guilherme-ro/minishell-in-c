## 🐚 Mini Shell em C

Este é um projeto de **Mini Shell** rudimentar implementado em **C**. Ele simula as funcionalidades básicas de um interpretador de linha de comando (shell) para sistemas **Unix-like** (como Linux, macOS, e WSL), utilizando chamadas de sistema POSIX essenciais como `fork()`, `execvp()`, e `waitpid()`.

O shell permite a execução de comandos externos (como `ls`, `echo`, `date`, `cat`, etc.) lidos a partir da entrada padrão.

----------

### ✨ Funcionalidades

-   **Execução de Comandos Externos:** Utiliza `fork()` para criar um novo processo filho, e `execvp()` para substituir a imagem do processo filho pelo programa a ser executado.
    
-   **Espera Síncrona (`waitpid`)**: O processo pai aguarda a conclusão da execução do comando pelo processo filho.
    
-   **Parsing de Linha de Comando:** Analisa a linha de entrada, dividindo o comando e seus argumentos (`tokens`) usando `strtok()`.
    
-   **Comando Interno `exit`:** Permite que o usuário saia do shell.
    
-   **Tratamento de Erros:** Inclui tratamento básico de erros para `fork()` e `execvp()`.
    

----------

### 💻 Requisitos

Este código é projetado para compilar e rodar em ambientes com suporte à API POSIX, o que inclui:

-   **Linux**
    
-   **macOS**
    
-   **Windows Subsystem for Linux (WSL)**
    
-   **Outros sistemas Unix-like**
    

> **⚠️ Atenção:** Ele não funciona nativamente no Windows sem ferramentas de compatibilidade como **Cygwin** ou **MinGW/MSYS2**.

----------

### 🔧 Como Compilar e Executar

Para compilar o projeto, você precisará de um compilador C, como o **GCC**.

#### 1. Compilação

Use o `gcc` para compilar o arquivo `mini_shell.c`:

Bash

```
gcc mini_shell.c -o mini_shell

```

Isso criará um arquivo executável chamado `mini_shell`.

#### 2. Execução

Execute o shell compilado usando o seguinte comando:

Bash

```
./mini_shell

```

#### 3. Uso

O shell será iniciado e apresentará o prompt `C_Shell>`. Você pode digitar comandos como faria em seu terminal padrão:

```
--- Mini Shell C (Para sistemas Unix-like) ---
Digite 'exit' para sair.
C_Shell> ls -l
total 16
-rwxr-xr-x 1 user user 8740 Nov 16 23:00 mini_shell
-rw-r--r-- 1 user user 2560 Nov 16 23:00 mini_shell.c
C_Shell> date
Mon Nov 17 01:14:17 -03 2025
C_Shell> exit

Mini Shell encerrado.

```

----------

### ⚙️ Detalhes da Implementação

A lógica central do shell reside na função `execute_command`, que segue o padrão de **`fork-exec-wait`**:

1.  **`fork()`**: Cria um processo filho.
    
2.  **Processo Filho**: Chama `execvp()` para executar o comando.
    
3.  **Processo Pai**: Chama `waitpid()` para aguardar a finalização do processo filho.
    

A função `parse_line` utiliza `strtok()` para dividir o comando lido em argumentos que são armazenados em um array de _strings_ (`char *args[]`) e passado para `execvp()`.
