add_library (src
  Speaker.h
  Speaker.cpp
  HelloWorld.cpp)

install (TARGETS src DESTINATION bin)
install (FILES Speaker.h DESTINATION include)
