void __kernel test(int temp)
{
  if (get_global_id(0) == 0 && get_global_id(1) == 2)
    printf("Hello world! %d", temp);
}