#include "utils.h"
#include "../../submodules/rpmalloc/rpmalloc/rpmalloc.h"

char* read_file(const char *filename) 
{
    FILE *file = NULL;
    long length = 0;
    char *content = NULL;
    size_t read_chars = 0;

    /* open in read binary mode */
    file = fopen(filename, "rb");
    if (file == NULL) {
        goto cleanup;
    }

    /* get the length */
    if (fseek(file, 0, SEEK_END) != 0) {
        goto cleanup;
    }
    length = ftell(file);
    if (length < 0) {
        goto cleanup;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        goto cleanup;
    }

    /* allocate content buffer */
    content = (char*)rpmalloc((size_t)length + sizeof(""));
    if (content == NULL) {
        goto cleanup;
    }

    /* read the file into memory */
    read_chars = fread(content, sizeof(char), (size_t)length, file);
    if ((long)read_chars != length) {
        rpfree(content);
        content = NULL;
        goto cleanup;
    }
    content[read_chars] = '\0';


cleanup:
    if (file != NULL) {
        fclose(file);
    }

    return content;
}

#pragma region stack
STK_stack STK_init()
{
    STK_stack s = rpmalloc(sizeof(*s));
    memset(s, 0, sizeof(*s));
    return s;
}

void STK_push(STK_stack *stack, int value)
{
    STK_stack new_stack;
    if ((*stack)->top == STACK_SIZE) {
        new_stack = STK_init();
        new_stack->next = (*stack);
        (*stack) = new_stack;
    }
    (*stack)->data[(*stack)->top] = value;
    (*stack)->top++;
}

int STK_pop(STK_stack *stack)
{
    STK_stack tmp;
    int ret = -1;

    if ((*stack) == NULL) {
        return -1;
    } 
    
    (*stack)->top--;
    // If the stack is empty and next is not NULL, pop the top of the next stack
    if ((*stack)->top == 0 && (*stack)->next != NULL) {
        tmp = (*stack)->next;
        free(*stack);
        (*stack) = tmp;
    }
    
    ret = (*stack)->data[(*stack)->top];
    
    return ret;
}

void STK_clear(STK_stack stack)
{
    if (stack->next) {
        STK_clear(stack->next);
    }
    rpfree(stack);
}
#pragma endregion
