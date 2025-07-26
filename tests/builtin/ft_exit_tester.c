#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

typedef struct {
    char *test_name;
    char *command;
    int expected_exit_code;
} test_case_t;

int run_shell_command(char *shell_path, char *command, char **output, char **error_output) {
    int pipefd_out[2], pipefd_err[2];
    pid_t pid;
    int status;
    char buffer[4096];
    int n;

    if (pipe(pipefd_out) == -1 || pipe(pipefd_err) == -1) {
        perror("pipe");
        return -1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        // Child process
        close(pipefd_out[0]);
        close(pipefd_err[0]);
        
        dup2(pipefd_out[1], STDOUT_FILENO);
        dup2(pipefd_err[1], STDERR_FILENO);
        
        close(pipefd_out[1]);
        close(pipefd_err[1]);

        // Execute shell with command
        execl(shell_path, shell_path, "-c", command, NULL);
        perror("execl");
        exit(1);
    } else {
        // Parent process
        close(pipefd_out[1]);
        close(pipefd_err[1]);

        // Read stdout
        n = read(pipefd_out[0], buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            *output = strdup(buffer);
        } else {
            *output = strdup("");
        }

        // Read stderr
        n = read(pipefd_err[0], buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            *error_output = strdup(buffer);
        } else {
            *error_output = strdup("");
        }

        close(pipefd_out[0]);
        close(pipefd_err[0]);

        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        return -1;
    }
}

int run_minishell_command(char *command, char **output, char **error_output) {
    return run_shell_command("./minishell", command, output, error_output);
}

int run_bash_command(char *command, char **output, char **error_output) {
    return run_shell_command("/bin/bash", command, output, error_output);
}

void print_test_result(char *test_name, int minishell_exit, int bash_exit, 
                      char *minishell_out, char *bash_out,
                      char *minishell_err, char *bash_err) {
    printf("\n" CYAN "=== %s ===" RESET "\n", test_name);
    printf(BLUE "Command: " RESET "%s\n", test_name);
    
    printf(YELLOW "Exit codes:" RESET "\n");
    printf("  Minishell: %d\n", minishell_exit);
    printf("  Bash:      %d\n", bash_exit);
    
    if (strlen(minishell_out) > 0 || strlen(bash_out) > 0) {
        printf(YELLOW "Stdout:" RESET "\n");
        printf("  Minishell: '%s'\n", minishell_out);
        printf("  Bash:      '%s'\n", bash_out);
    }
    
    if (strlen(minishell_err) > 0 || strlen(bash_err) > 0) {
        printf(YELLOW "Stderr:" RESET "\n");
        printf("  Minishell: '%s'\n", minishell_err);
        printf("  Bash:      '%s'\n", bash_err);
    }
    
    if (minishell_exit == bash_exit) {
        printf(GREEN "✓ PASS" RESET "\n");
    } else {
        printf(RED "✗ FAIL" RESET "\n");
    }
}

void run_test(char *test_name, char *command) {
    char *minishell_out, *minishell_err;
    char *bash_out, *bash_err;
    int minishell_exit, bash_exit;

    printf(MAGENTA "Running test: %s" RESET "\n", test_name);

    minishell_exit = run_minishell_command(command, &minishell_out, &minishell_err);
    bash_exit = run_bash_command(command, &bash_out, &bash_err);

    print_test_result(test_name, minishell_exit, bash_exit,
                     minishell_out, bash_out, minishell_err, bash_err);

    free(minishell_out);
    free(minishell_err);
    free(bash_out);
    free(bash_err);
}

int main() {
    printf(CYAN "=== MINISHELL EXIT TESTER ===" RESET "\n");
    printf("Comparing minishell exit behavior with bash\n");
    
    // Check if minishell exists
    if (access("./minishell", F_OK) == -1) {
        printf(RED "Error: ./minishell not found. Please compile first.\n" RESET);
        return 1;
    }

    test_case_t tests[] = {
        {"exit", "exit", 0},
        {"exit 0", "exit 0", 0},
        {"exit 1", "exit 1", 1},
        {"exit 42", "exit 42", 42},
        {"exit 255", "exit 255", 255},
        {"exit 256", "exit 256", 0},  // 256 % 256 = 0
        {"exit -1", "exit -1", 255},  // -1 % 256 = 255
        {"exit abc", "exit abc", 2},  // bash exits with 2 for non-numeric
        {"exit 1 2", "exit 1 2", 1},  // bash uses first arg and shows error
        {"exit 999999999999999999999", "exit 999999999999999999999", 255},
        {"exit +42", "exit +42", 42},
        {"exit -42", "exit -42", 214},  // -42 % 256 = 214
        {"exit 00", "exit 00", 0},
        {"exit 007", "exit 007", 7},
        {"exit ''", "exit ''", 0},
        {"exit \"\"", "exit \"\"", 0},
        {NULL, NULL, 0}
    };

    int i = 0;
    int passed = 0, total = 0;
    
    while (tests[i].test_name != NULL) {
        run_test(tests[i].test_name, tests[i].command);
        
        // Simple pass/fail check (you might want to make this more sophisticated)
        char *minishell_out, *minishell_err;
        char *bash_out, *bash_err;
        int minishell_exit = run_minishell_command(tests[i].command, &minishell_out, &minishell_err);
        int bash_exit = run_bash_command(tests[i].command, &bash_out, &bash_err);
        
        if (minishell_exit == bash_exit) {
            passed++;
        }
        total++;
        
        free(minishell_out);
        free(minishell_err);
        free(bash_out);
        free(bash_err);
        
        i++;
    }

    printf("\n" CYAN "=== SUMMARY ===" RESET "\n");
    printf("Passed: %d/%d\n", passed, total);
    
    if (passed == total) {
        printf(GREEN "All tests passed! 🎉" RESET "\n");
        return 0;
    } else {
        printf(RED "Some tests failed. 😞" RESET "\n");
        return 1;
    }
}
