void __kernel test()
{
  if(get_global_id(0))
    printf("Hello world!");
}