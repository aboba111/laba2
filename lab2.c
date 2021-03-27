#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    int value;
    struct Stack* next;
} Stack;

void push(Stack** head, int value) {
    Stack* tmp = (Stack*)malloc(sizeof(Stack));
    //printf("Pushed %i\n", value);
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}

int pop(Stack** head) {
    if (head)
    {
        Stack* out;
        int ret;
        out = *head;
        *head = (*head)->next;
        ret = out->value;
        free(out);
        //printf("popped %i\n", ret);
        return ret;
    }
    printf("Cannot pop empty stack\n");
    return 0;
}

int  cs(char a)
{
    if (a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' || a == '6' || a == '7' || a == '8' || a == '9')return 1;
    if (a == '*')return 2;
    if (a == '/')return 3;
    if (a == '+')return 4;
    if (a == '-')return 5;
    if (a == '=')return 6;

    return 0;
}
int calculate(Stack** operands)
{
    char str[100];
    scanf("%99[^\n]%*c", &str);
    int a = 0, b = 0;
    int ch = 0, buff;
    int result = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        
        if (str[i] == '\n' || str[i] == '\0')
        {
            return result;
        }
        switch (cs(str[i]))
        {
        case 1:
            buff = atoi(&str[i]);
            ch = 0;
            while (buff >= 10)
            {
                buff = buff / 10;
                ch++;
            }
            push(operands, atoi(&str[i]));
            i += ch;
            break;

        case 2:
            b = pop(operands);
            a = pop(operands);
            result += a * b;
            push(operands, result);
            result = 0;
            break;

        case 3:
            b = pop(operands);
            if (b == 0)
            {
                printf("You can't devide by zero\n");
                return 0;
            }
            a = pop(operands);
            result += a / b;
            push(operands, result);
            result = 0;
            break;

        case 4:

            b = pop(operands);
            a = pop(operands);
            result += a + b;
            push(operands, result);
            result = 0;
            break;

        case 5:
            b = pop(operands);
            a = pop(operands);
            result += a - b;
            push(operands, result);
            result = 0;
            break;

        case 6:
            i=strlen(str);
            break;
        }
    }
    result = pop(operands);
    return result;
}

int main()
{
    Stack* stack = NULL;
    int a = calculate(&stack);
    printf("Your result is: %i\n", a);
    while (stack)
    {
        pop(&stack);
    }
    return 0;
}