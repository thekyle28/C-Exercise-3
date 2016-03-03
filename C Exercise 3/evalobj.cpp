#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "evalobj.h"



struct env *envglb; //global variables

//creates a new env with one variable.
struct env *mkenv(string varName, int value){
    struct env *env = new struct env;
    env->var = varName;
    env->value = value;
    env->next = NULL;
    return env;
}

struct env *copyEnv(struct env *env){
    // if the environment is null then return a dummy environment
    if (!env){
        return mkenv("", 0);
    }
    // the head element
    struct env *newEnv = new struct env;
    struct env *first = newEnv; //first points to the first element in the list.
    newEnv->var = env->var;
    newEnv->value = env->value;

    //the rest of the environment
    env = env->next;
    while (env) { //makes sure that the environment isn't null
        newEnv->next = new struct env;
        newEnv = newEnv->next;
        newEnv->var = env->var;
        newEnv->value = env->value;
        env = env->next;
    }
    newEnv->next = NULL;
    return first;
} //fairly sure copy is correct.

//adds a variable to an environment and overrides it if it already exists.
void addVarOverride(string var, int value, struct env *env)
{
    while (env->next){ //checks that the next pointer is not null.
        if (var==env->var){ //if the variables have the same name, overwrite the variable value with the new one.
            env->value = value;
        }
        env = env->next; //if the next pointer is not null then move along the list.
    }
    //the last variable would have been reached at this point in the code.
    if (var == env->var){ //if the variables have the same name, overwrite the variable value with the new one.
        env->value = value;
    }
    else //otherwise add it to the end of the environment list.
        env->next = mkenv(var, value);

}

//adds variables without overwriting values, and doesn't add the variable if it is already in the environment.
void addVar(string var, int value, struct env *env)
{
    while (env->next){ //checks that the next pointer is not null.
        if (var == env->var){ //if the variables have the same name, overwrite the variable value with the new one.
            return;
        }
        env = env->next; //if the next pointer is not null then move along the list.
    }
    //the last variable would have been reached at this point in the code.
    if (var == env->var){ //if the variables have the same name, overwrite the variable value with the new one.
        return;
    }
    else //otherwise add it to the end of the environment list.
        env->next = mkenv(var, value);

}

//returns the value for a given variable in a list of variables and values.
int getval(string var, struct env *env){
    if (env){ //check that the environment is not null
        if (var == env->var) //if the variable names are the same
            return env->value; //return the value
        else
            return getval(var, env->next); //check the next environment struct for the variable.
    }
    else {
        char str[20];
        //strcat(str, "Error variable not found");
        printf("%s\n", str);
        return -1;
    }
}

int evalexplist2(class ExpList *el, enum op op, struct env *env){
    if (!(el)){ //if the head is NULL i.e. the list is empty
        switch (op){
        case plusop:
            return 0; //if it is a sum operation return 0 so it doesn't affect the result.
        case timesop:
            return 1; // if it is a multiplication operation return 1 so that it doesn't affect the result.
        }
    }

    else{ //otherwise if the head isn't NULL
        switch (op){
        case plusop:
            //Add the evaluation of the head of the expression to the rest of the list.
            return el->head->eval(env) + evalexplist2(el->tail, op, env);
        case timesop:
            //Multiply the evaluation of the head of the expression to the rest of the list.
            return el->head->eval(env) * evalexplist2(el->tail, op, env);
        }
    }
}

int Constant::eval(struct env *e){
    return n;
}

int Var::eval(struct env *e){
    return getval(this->name, e);
}

int Let::eval(struct env *e){
    struct env *copy;
    copy = copyEnv(e);
    addVarOverride(this->bvar, bexp->eval(copy), copy);
    addVar(this->bvar, bexp->eval(copy), copy);
    return body->eval(copy);
}

int OpApp::eval(struct env *e){
    return evalexplist2(this->args, this->op, e);
}