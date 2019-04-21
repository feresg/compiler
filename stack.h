// stack.h : stack representation in C 
#ifndef STACK_H
#define STACK_H

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
  
// A structure to represent a stack 
struct Stack { 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* create_stack(unsigned capacity) { 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*) malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 
  
// Stack is full when top is equal to the last index 
int is_full(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
} 
  
// Stack is empty when top is equal to -1 
int is_empty(struct Stack* stack) {
    return stack->top == -1;
} 
  
// Function to add an item to stack.  It increases top by 1 
void push(struct Stack* stack, int item) { 
    if (is_full(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    // printf("\t%d pushed to stack\n", item); 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
void pop(struct Stack* stack) { 
    if (is_empty(stack)) 
        printf("popping error: empty stack");
        // return INT_MIN; 
    stack->top--;
    // printf()
    // printf("\t%d popped from stack\n", stack->array[stack->top--]); 
}

int top(struct Stack* stack) {
    if (is_empty(stack))
        return -1;
    return stack->array[stack->top];
}

#endif