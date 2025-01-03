#include "lib.c"

int LLVMFuzzerTestOneInput(u8 *buf, size_t len) {
    arena_scratch1 = arena_create(0x1000 * 0x1000);
    arena_scratch2 = arena_create(0x1000 * 0x1000);

    // Ignore empty inputs as they cannot be passed into the real program after
    // argument parsing.
    if (len == 0) {
        return -1;
    }

    Str input = (Str){buf, len};

    // Like `test_single_expr`, but without asserts for parsing/tokenizing
    // fails.

    ArenaTemp scratch = arena_get_scratch(NULL);

    LexRetRes tokens = lex(scratch.arena, input);
    if (!tokens.is_ok) {
        return -1;
    }

    ParseRetRes ast_ = parse(scratch.arena, tokens.ok.tokens);
    if (!ast_.is_ok) {
        return -1;
    }
    Ast *ast = ast_.ok.ast;

    Num res_interpret = mode_interpret_ast(ast);
    Num res_jit = mode_jit_ast(ast);
    Num res_vm = mode_vm_ast(ast);
    Num res_compile = mode_compile_ast(ast, Str("/tmp/out"));

    assert(res_interpret == res_jit && res_interpret == res_vm &&
           res_interpret == res_compile &&
           "Different implementations do not agree with each other on the "
           "resulting value of the evaluated expression");
    arena_release_scratch(scratch);

    arena_destroy(&arena_scratch1);
    arena_destroy(&arena_scratch2);

    return 0;
}
