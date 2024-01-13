#if defined(__cplusplus)
extern "C" {
__attribute__((constructor))
void one_print()
{
    __builtin_printf("one_print\n");
}
#endif 



#if defined(__cplusplus)
extern "C" {
__attribute__((constructor))
void second_print()
{
    __builtin_printf("second_print\n");
}
#endif 



#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)
}
#endif