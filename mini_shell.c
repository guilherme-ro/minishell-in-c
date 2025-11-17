#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // Para fork, execvp, getpid
#include <sys/wait.h>   // Para wait
#include <sys/types.h>  // Para pid_t

// Constante para o tamanho maximo da linha de comando
#define MAX_LINE 1024 
// Constante para o numero maximo de argumentos/tokens
#define MAX_ARGS 64

/**
 * Funcao para analisar a linha de comando do usuario.
 * Divide a string de entrada em tokens (argumentos) separados por espacos.
 * * @param line A string contendo o comando e seus argumentos.
 * @param args O array de ponteiros para onde os tokens serao salvos.
 * @return O numero de argumentos encontrados.
 */
int parse_line(char *line, char **args) {
    char *p;
    int count = 0;

    // O strtok() divide a string com base no delimitador (' ' neste caso)
    // O primeiro argumento e a string, os seguintes sao NULL para continuar a divisao
    p = strtok(line, " \n\t"); 

    while (p != NULL && count < MAX_ARGS - 1) {
        args[count++] = p;
        p = strtok(NULL, " \n\t");
    }
    args[count] = NULL; // O array de argumentos deve terminar com NULL para execvp
    
    return count;
}

/**
 * Funcao principal para execucao do comando.
 * Usa fork() para criar um novo processo.
 * * @param args O array de argumentos (comando e parametros).
 */
void execute_command(char **args) {
    pid_t pid, wpid;
    int status;

    // 1. Cria um novo processo (child process)
    pid = fork(); 

    if (pid == 0) {
        // --- PROCESSO FILHO (CHILD PROCESS) ---
        // O execvp substitui a imagem do processo filho pelo novo programa
        // args[0] e o nome do comando (ex: "ls")
        // args e o array de argumentos (ex: {"ls", "-l", NULL})
        if (execvp(args[0], args) == -1) {
            perror("mini_shell: Erro ao executar comando");
            exit(EXIT_FAILURE); // Sai do processo filho em caso de erro
        }
    } else if (pid < 0) {
        // --- ERRO ---
        perror("mini_shell: Erro ao criar processo (fork)");
    } else {
        // --- PROCESSO PAI (PARENT PROCESS) ---
        // O processo pai espera o filho terminar
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

// --- FUNCAO PRINCIPAL ---

int main(void) {
    char line[MAX_LINE];       // Buffer para a linha de entrada
    char *args[MAX_ARGS];      // Array de ponteiros para os argumentos
    int running = 1;

    printf("--- Mini Shell C (Para sistemas Unix-like) ---\n");
    printf("Digite 'exit' para sair.\n");

    while (running) {
        printf("C_Shell> ");
        
        // Le a linha de comando do usuario
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            // Em caso de EOF (Ctrl+D), sai do loop
            running = 0;
            break;
        }

        // Se a linha estiver vazia ou for apenas um '\n', continua o loop
        if (line[0] == '\n') {
            continue;
        }

        // Analisa a linha e preenche o array 'args'
        parse_line(line, args);

        // Verifica se o comando e o comando interno 'exit'
        if (args[0] == NULL) {
            continue; // Linha em branco
        } else if (strcmp(args[0], "exit") == 0) {
            running = 0;
            continue;
        }
        
        // Executa o comando externo
        execute_command(args);
    }

    printf("\nMini Shell encerrado.\n");
    return 0;
}