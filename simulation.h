/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
#include "server_type.h"

// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.


void visit(User_t& user1,User_t& user2);
void trending(int n,int total,const User_t user[]);
void refresh(User_t& user1);
void follow(User_t& user1,User_t& user2);
void unfollow(User_t& user1,User_t& user2);
void like(User_t& user1,Post_t& post);
void unlike(User_t& user1,Post_t& post);
void comment(User_t& user1,Post_t& post,string text);
void uncomment(User_t& user1,Post_t& post,int comment_id);
void post(User_t& user1,string title,string tag[],int num_tags,string text);
void unpost(User_t& user1,int post_id);


/* Helper Functions */
int searchname(string name, int total,const User_t user[]);
bool a_is_following_b (User_t& user1,User_t& user2);

// Printing
void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);
bool compare(const Tag_t x,const Tag_t y);


