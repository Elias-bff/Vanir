#ifndef HOOKS_H
#define HOOKS_H

#include <lua.h>

int hooksInit(lua_State* L);

enum dataTypes {
    number,
    string,
    function,
};

struct callbacks {
    size_t dataSize;
    void* data;
    enum dataTypes dataType;
};

struct hookPool {
    struct hook *hooks;
    int count;
};

struct hook {
    const char *hookName;
    struct stack *stack;
    size_t pool;
    struct hook *address;
};

struct stack {
    const char *name;
    void (*func)(lua_State*, int, struct hook *instance, struct callbacks* callback);
    int ref;
};

void registerHook(struct hookPool* pool, struct hook hookData);
void addHook(struct hook *instance, const char *name, void (*func)(lua_State*, int, struct hook *instance, struct callbacks* callback), int ref);
void runHook(struct hook *instance, lua_State *L, struct callbacks* callback);
void freeHook(struct hook *instance, lua_State *L);

struct callbacks* createCallback(size_t dataSize, enum dataTypes dataType);
void* getCallback(const struct callbacks* callback);
void setCallback(struct callbacks* callback, const void* data);

extern struct hookPool pool;

extern struct hook think;

#endif
