/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */
#include "simulation.h"

void visit(User_t& user1,User_t& user2){
    cout<<">> visit"<<endl;
    string relationship;
    string name1=user1.username;
    string name2=user2.username;
    if(name1==name2){
        relationship="";
        printUser(user2,relationship);
    }
    else if(a_is_following_b(user1, user2)){
        if(a_is_following_b(user2, user1)){
            relationship="friend";
            printUser(user2,relationship);
        }
        else{
            relationship="following";
            printUser(user2,relationship);
        }
    }
    else if(!a_is_following_b(user1, user2)){
        relationship="stranger";
        printUser(user2,relationship);
    }
}



void trending(int n,int total,const User_t user[]){
    string tagname[1000];
    string unique_tag[1000];
    int m=0;
    int count=0;
    int flag=0;
    //record all tag names,including repeated tags
    for (int i=0;i<total;i++){
        for (int j=0;j<user[i].num_posts;j++){
            for (int k=0;k<user[i].posts[j].num_tags;k++){
                tagname[m]=user[i].posts[j].tags[k];
                m++;
            }
        }
    }
    //sort the tags
    for (int i=0;i<m;i++){
        if(count==0){unique_tag[0]=tagname[0];count++;continue;}
        for(int j=0;j<i;j++){
            if(tagname[i]==tagname[j]){flag=1;}
        }
        if (flag==0){unique_tag[count]=tagname[i];count++;}
    }
    //compute scores for each tag
    Tag_t tag[1000];
    for (int i=0;i<count;i++){
        tag[i].tag_content=unique_tag[i];
        tag[i].tag_score=0;
    }
    for (int i=0;i<total;i++) {
        for (int j = 0; j < user[i].num_posts; j++) {
            for (int k = 0; k < user[i].posts[j].num_tags; k++) {
                for (int p=0;p<count;p++){
                    if (user[i].posts[j].tags[k]==tag[p].tag_content){
                        tag[p].tag_score+=5+user[i].posts[j].num_likes+3*user[i].posts[j].num_comments;
                    }
                }
            }
        }
    }
    //use sort
    sort(tag, tag+count, compare);
    //print
    if (n>=count){n=count;}
    cout<<">> trending"<<endl;
    for (int i=0;i<n;i++){
        cout<<i+1<<" "<<tag[i].tag_content<<": "<<tag[i].tag_score<<endl;
    }
}

void refresh(User_t& user1){
    cout<<">> refresh"<<endl;
    for (int i=0;i<user1.num_posts;i++){
        printPost(user1.posts[i]);
    }
    for (int i=0;i<user1.num_following;i++){
        for (int j=0;j<user1.following[i]->num_posts;j++){
            printPost(user1.following[i]->posts[j]);
        }
    }
}

void follow(User_t& user1,User_t& user2){
    cout<<">> follow"<<endl;
    user1.num_following++;
    user1.following[user1.num_following-1]=&user2;
    user2.num_followers++;
    user2.follower[user2.num_followers-1]=&user1;
}

void unfollow(User_t& user1,User_t& user2){
    cout<<">> unfollow"<<endl;
    int i,j;
    for (i=0;i<user1.num_following;i++){
        if (user1.following[i]->username==user2.username){break;}
    }
    for (j=i+1;j<user1.num_following;j++){
        user1.following[j-1]=user1.following[j];
    }
    user1.num_following--;

    for (i=0;i<user2.num_followers;i++){
        if (user2.follower[i]->username==user1.username){break;}
    }
    for (j=i+1;j<user2.num_followers;j++){
        user2.follower[j-1]=user2.follower[j];
    }
    user2.num_followers--;
}

void like(User_t& user1,Post_t& post){
    cout<<">> like"<<endl;
    post.num_likes++;
    post.like_users[post.num_likes-1]=&user1;
}

void unlike(User_t& user1,Post_t& post){
    cout<<">> unlike"<<endl;
    int i,j;
    for (i=0;i<post.num_likes;i++){
        if (post.like_users[i]->username ==user1.username){break;}
    }
    for (j=i+1;j<post.num_likes;j++){
        post.like_users[j-1]=post.like_users[j];
    }
    post.num_likes--;
}

void comment(User_t& user1,Post_t& post,string text){
    cout<<">> comment"<<endl;
    post.num_comments++;
    post.comments[post.num_comments-1].user=&user1;
    post.comments[post.num_comments-1].text=text;
}

void uncomment(User_t& user1,Post_t& post,int comment_id){
    cout<<">> uncomment"<<endl;
    int j;
    for (j=comment_id;j<post.num_comments;j++){
        post.comments[j-1]=post.comments[j];
    }
    post.num_comments--;
}

void post(User_t& user1,string title,string tag[],int num_tags, string text){
    cout<<">> post"<<endl;
    int id=user1.num_posts;
    user1.num_posts++;
    user1.posts[id].num_comments=0;
    user1.posts[id].num_likes=0;
    user1.posts[id].num_tags=num_tags;
    user1.posts[id].title=title;
    user1.posts[id].text=text;
    user1.posts[id].owner=&user1;
    for(int i=0;i<num_tags;i++){
        user1.posts[id].tags[i]=tag[i];
    }
}

void unpost(User_t& user1,int post_id){
    cout<<">> delete"<<endl;
    int j;
    for (j=post_id;j<user1.num_posts;j++){
        user1.posts[j-1]=user1.posts[j];
    }
    user1.num_posts--;
}
/* Helper Functions */

int searchname(string name, int total,const User_t user[]){
    //EFFECT:takes the name you want to find in the namelist and returns its position
    int k;
    for ( k=0;k<total;k++){
        if (name==user[k].username){break;}
    }
    return k;
}

bool compare(const Tag_t x,const Tag_t y){
    int a=(int)x.tag_score;
    int b=(int)y.tag_score;
    if (a==b){return x.tag_content>y.tag_content;}
    return a>b;
}

bool a_is_following_b (User_t& user1,User_t& user2){
    for(int i=0;i<user1.num_following;i++){
        if(user1.following[i]->username==user2.username){
            return true;
        }
    }
    return false;
}
// Printing

void printUser(User_t& user, const string& relationship){
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}


void printPost(Post_t& post){
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for(unsigned int i = 0; i<post.num_tags; ++i){
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0){
        cout << "Comments:" << endl;
        for(unsigned int i = 0; i<post.num_comments; ++i){
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}


void printTag(const Tag_t& tag, unsigned int rank){
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
