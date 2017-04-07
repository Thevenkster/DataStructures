// Copyright (c) 2016 Andrew Sutton
// All rights reserved

#ifndef IMDB_DB_HPP
#define IMDB_DB_HPP

#include "movies.hpp"
#include "actors.hpp"
#include "roles.hpp"
#include <queue>

struct Vertex
{
  //identifier
  int key;
  std::string name;
  //actor / movie objects
  actor star;
  movie film;

  Vertex() = default;
  //actor vertex
  Vertex(actor a, int i)
    :star(a), key(i), film(), name()
  {}
  //movie vertex
  Vertex(movie m, int i)
    :film(m), key(i), star(), name()
  {}
  //constructor used for establishing link to actor.
  Vertex(actor a, int i, const std::string& x)
    :star(a), key(i), name(x)
  {}

};

struct database
{
  database();

  std::vector<int> distance; //kevin bacon # storage
  std::vector<Vertex> path; //path to kevin bacon.

  int add_movie(const char* name, const char* year);
  int find_movie(const char* name);

  int add_actor(const char* name);
  int find_actor(const char* name);

  int find_actor(const std::string& name);
  int add_role(const char* act, const char* mov, const char* info);

  //compute bacon number
  void BaconNumber();
  //Perform a breath first search to find actor
  void BFS(Vertex v);
  //Displays the movies and actors linking the given actor and kevin bacon
  int Display(const std::string& actor);

  // Storage for movies and actors.
  movie_table movies;
  actor_table actors;
  role_table roles;

  // Efficient lookup for movie and actor names.
  name_index movie_lookup;
  name_index actor_lookup;

  int movie_lookup_errors = 0;
};


#endif
