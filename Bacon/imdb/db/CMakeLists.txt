SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(db
  table.cpp
  movies.cpp
  actors.cpp
  roles.cpp
  db.cpp
)
