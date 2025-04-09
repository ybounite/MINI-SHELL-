#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for the AST nodes
typedef enum { CMD = 0, PIPE = 10 } NodeType;

typedef struct ASTNode {
	NodeType type;
	char *value;
	struct ASTNode *left;
	struct ASTNode *right;
} ASTNode;

// Function to create a new AST node
ASTNode* new_node(NodeType type, char *value) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

void print_ast(ASTNode *node) {
    if (!node) return;
    if (node->type == CMD)
        printf("CMD: %s\n", node->value);
    else if (node->type == PIPE)
        printf("PIPE\n");
    
    if (node->left) print_ast(node->left);
    if (node->right) print_ast(node->right);
}

// Example function to execute a simple command
void execute_cmd(ASTNode *node) {
    if (node->type == CMD) {
        printf("Executing command: %s\n", node->value);
        // Here you would use exec() to actually run the command
        // For simplicity, we just print it.
    } else if (node->type == PIPE) {
        // Handle piping logic
        printf("Piping commands...\n");
        execute_cmd(node->left);
        execute_cmd(node->right);
    }
}

int main() {
    // Example AST for "ls -l | grep txt"
    ASTNode *cmd1 = new_node(CMD, "ls");
    ASTNode *arg1 = new_node(CMD, "-l");
    cmd1->left = arg1;

    ASTNode *cmd2 = new_node(CMD, "grep");
    ASTNode *arg2 = new_node(CMD, "txt");
    cmd2->left = arg2;

    ASTNode *pipe = new_node(PIPE, "|");
    pipe->left = cmd1;
    pipe->right = cmd2;

    // Print the AST for debugging
    print_ast(pipe);

    // Execute the commands
    execute_cmd(pipe);
	ft_free_node();
    return 0;
}
