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
            for(int q=0;q<1000;q++){content[q]="";}
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
                user[i].posts[j].tags[l]=content[n].substr(1,content[n].rfind("#")-1);
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
    //Now read logfile
    ifstream log;
    string logname=argv[2];
    for(int q=0;q<1000;q++){content[q]="";}
    log.open(logname);
    if (log) {
        n=0;
        while (getline(log, content[n])) {n++;}
    }
    log.close();
    //cout<<content[5]<<endl;
    //cout<<user[2].posts[0].text<<endl;
    //printPost(user[0].posts[0]);
    //string str="abc abc def";
    //int c=(str.find("cab")==str.npos);
    //visit(user[6],user[3]);
    //refresh(user[3]);
    //visit(user[searchname("zhuzhuoer",total_users,user)],user[searchname("marstin",total_users,user)]);
    //follow(user[searchname("zhuzhuoer",total_users,user)],user[searchname("marstin",total_users,user)]);
    //visit(user[searchname("zhuzhuoer",total_users,user)],user[searchname("marstin",total_users,user)]);
    //unfollow(user[searchname("zhuzhuoer",total_users,user)],user[searchname("paul.weng",total_users,user)]);
    //for (int pp=0;pp<user[0].num_followers;pp++){
    //    cout<<user[0].follower[pp]->username<<endl;
    //}
    //visit(user[searchname("zhuzhuoer",total_users,user)],user[searchname("marstin",total_users,user)]);
    //cout<<user[searchname("zhuzhuoer",total_users,user)].following[2]->username<<endl;
    //refresh(user[3]);
    //like(user[searchname("zhuzhuoer",total_users,user)],user[searchname("marstin",total_users,user)].posts[0]);
    //refresh(user[3]);
    unpost(user[0],2);
    refresh(user[0]);
    return 0;

}
