add_library (lambda
  STATIC
  lambda/helloworld.c)

install (TARGETS lambda DESTINATION bin)
install (FILES lambda/helloworld.c DESTINATION include)
