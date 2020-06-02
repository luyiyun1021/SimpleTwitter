#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
#include "simulation.h"

int main(int argc,char *argv[]) {
    //read username and the directory of user info
    ifstream namefile;
    string username=argv[1];
    string folder;
    string name[100];
    int total_users;
    namefile.open(username);
    if (namefile) {
        int i=0;
        getline(namefile, folder);
        while (getline(namefile, name[i])) {i++;}
        total_users=i;
    }
    namefile.close();
    //assign name to user
    struct User_t user[MAX_USERS];
    for (int i=0;i<total_users;i++){
        user[i].username=name[i];
    }
    //read user info
    string path;
    ifstream info;
    string num_posts,num_following,num_followers;
    string following[MAX_FOLLOWING];
    string follower[MAX_FOLLOWERS];
    for (int i=0;i<total_users;i++){
        path="./"+folder+"/"+user[i].username+"/user_info";
        info.open(path);
        if (info) {
            getline(info, num_posts);
            getline(info, num_following);
            for (int j=0;j<atoi(num_following.c_str());j++){
                getline(info, following[j]);
            }
            getline(info, num_followers);
            for (int j=0;j<atoi(num_followers.c_str());j++){
                getline(info, follower[j]);
            }
        }
        info.close();
        user[i].num_posts=atoi(num_posts.c_str());
        user[i].num_following=atoi(num_following.c_str());
        user[i].num_followers=atoi(num_followers.c_str());
        for (int j=0;j<atoi(num_following.c_str());j++){
            user[i].following[j]=&user[searchname(following[j],total_users,user)];
        }
        for (int j=0;j<atoi(num_followers.c_str());j++){
            user[i].follower[j]=&user[searchname(follower[j],total_users,user)];
        }
    }
    //read post info
    ifstream post;
    string content[1000];
    int n=0,l=0;
    for (int i=0;i<total_users;i++){
        for (int j=0;j<user[i].num_posts;j++){
            for(int q=0;q<1000;q++){content[q]="0";}
            path="./"+folder+"/"+user[i].username+"/posts/"+to_string(j+1);
            post.open(path);
            if (post) {
                n=0;
                while (getline(post, content[n])) {n++;}
            }
            post.close();
            l=0;
            n=1;
            user[i].posts[j].title=content[0];
            while(content[n].find_first_of("#")==0){
                user[i].posts[j].tags[l]=content[n];
                n++;l++;
            }
            user[i].posts[j].num_tags=l;
            user[i].posts[j].text=content[n];
            n++;
            user[i].posts[j].num_likes=atoi(content[n].c_str());
            n++;
            for (int k=0;k<user[i].posts[j].num_likes;k++){
                user[i].posts[j].like_users[k]=&user[searchname(content[n],total_users,user)];
                n++;
            }
            user[i].posts[j].num_comments=atoi(content[n].c_str());
            n++;
            for (int k=0;k<user[i].posts[j].num_comments;k++){
                user[i].posts[j].comments[k].user= &user[searchname(content[n],total_users,user)];
                n++;
                user[i].posts[j].comments[k].text=content[n];
                n++;
            }
            user[i].posts[j].owner=&user[i];
        }
    }
    //Server Initialization part has completed
    cout<<user[0].posts[1].owner->follower[1]->username<<endl;
    return 0;
}
