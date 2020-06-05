#include "simulation.h"

int main(int argc,char *argv[]) {
    try{
        if(argc < 3){
            ostringstream oStream;
            oStream << "Error: Wrong number of arguments!" << endl;
            oStream << "Usage: ./p2 <username> <logfile>" << endl;
            throw Exception_t(INVALID_ARGUMENT, oStream.str());
        } }
    catch (Exception_t &exception){
        cout << exception.error_info;
        return 0; }
    //read username and the directory of user info
    ifstream namefile;
    string username=argv[1];
    string folder;
    string name[100];
    int total_users=0;
    namefile.open(username);
    try{
        if(!namefile){
            ostringstream oStream;
            oStream << "Error: Cannot open file "<<username<<"!" << endl;
            throw Exception_t(FILE_MISSING, oStream.str());
        } }
    catch (Exception_t &exception){
        cout << exception.error_info;
        return 0; }

    if (namefile) {
        int i=0;
        getline(namefile, folder);
        while (getline(namefile, name[i])) {i++;}
        total_users=i;
    }
    namefile.close();
    //assign name to user
    try{
        if(total_users>MAX_USERS){
            ostringstream oStream;
            oStream << "Error: Too many users! " << endl;
            oStream << "Maximal number of users is "<<MAX_USERS<<"." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        } }
    catch (Exception_t &exception){
        cout << exception.error_info;
        return 0; }
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
        path=folder+"/"+user[i].username+"/user_info";
        info.open(path);
        try{
            if(!info){
                ostringstream oStream;
                oStream << "Error: Cannot open file "<<path<<"!" << endl;
                throw Exception_t(FILE_MISSING, oStream.str());
            } }
        catch (Exception_t &exception){
            cout << exception.error_info;
            return 0; }
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
        try{
            if(user[i].num_posts>MAX_POSTS){
                ostringstream oStream;
                oStream << "Error: Too many posts for user " <<user[i].username<<"!" << endl;
                oStream << "Maximal number of posts is "<<MAX_POSTS<<"." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
            }
            if(user[i].num_following>MAX_FOLLOWING){
                ostringstream oStream;
                oStream << "Error: Too many followings for user " <<user[i].username<<"!" << endl;
                oStream << "Maximal number of followings is "<<MAX_FOLLOWING<<"." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
            }
            if(user[i].num_followers>MAX_FOLLOWERS){
                ostringstream oStream;
                oStream << "Error: Too many followers for user " <<user[i].username<<"!" << endl;
                oStream << "Maximal number of followers is "<<MAX_FOLLOWERS<<"." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
            }
        }
        catch (Exception_t &exception){
            cout << exception.error_info;
            return 0; }
        for (int j=0;j<atoi(num_following.c_str());j++){
            user[i].following[j]=&user[searchname(following[j],total_users,user)];
        }
        for (int j=0;j<atoi(num_followers.c_str());j++){
            user[i].follower[j]=&user[searchname(follower[j],total_users,user)];
        }
    }
    //read post info
    ifstream Post;
    string content[1000];
    int n=0,l=0;
    for (int i=0;i<total_users;i++){
        for (int j=0;j<user[i].num_posts;j++){
            for(int q=0;q<1000;q++){content[q]="";}
            path=folder+"/"+user[i].username+"/posts/"+to_string(j+1);
            Post.open(path);
            try{
                if(!Post){
                    ostringstream oStream;
                    oStream << "Error: Cannot open file "<<path<<"!" << endl;
                    throw Exception_t(FILE_MISSING, oStream.str());
                } }
            catch (Exception_t &exception){
                cout << exception.error_info;
                return 0; }
            if (Post) {
                n=0;
                while (getline(Post, content[n])) {n++;}
            }
            Post.close();
            l=0;
            n=1;
            user[i].posts[j].title=content[0];
            int tmp=n;
            while(content[tmp].find_first_of("#")==0){
                tmp++;l++;
            }
            user[i].posts[j].num_tags=l;
            try{
                if(user[i].posts[j].num_tags>MAX_TAGS){
                    ostringstream oStream;
                    oStream << "Error: Too many tags for post " <<user[i].posts[j].title<<"!" << endl;
                    oStream << "Maximal number of tags is "<<MAX_TAGS<<"." << endl;
                    throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
                }}
            catch (Exception_t &exception){
                cout << exception.error_info;
                return 0; }
            l=0;
            while(content[n].find_first_of("#")==0){
                user[i].posts[j].tags[l]=content[n].substr(1,content[n].rfind("#")-1);
                n++;l++;
            }

            user[i].posts[j].text=content[n];
            n++;
            user[i].posts[j].num_likes=atoi(content[n].c_str());
            try{
                if(user[i].posts[j].num_likes>MAX_LIKES){
                    ostringstream oStream;
                    oStream << "Error: Too many likes for post " <<user[i].posts[j].title<<"!" << endl;
                    oStream << "Maximal number of likes is "<<MAX_LIKES<<"." << endl;
                    throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
                }}
            catch (Exception_t &exception){
                cout << exception.error_info;
                return 0; }
            n++;
            for (int k=0;k<user[i].posts[j].num_likes;k++){
                user[i].posts[j].like_users[k]=&user[searchname(content[n],total_users,user)];
                n++;
            }
            user[i].posts[j].num_comments=atoi(content[n].c_str());
            try{
                if(user[i].posts[j].num_comments>MAX_COMMENTS){
                    ostringstream oStream;
                    oStream << "Error: Too many comments for post " <<user[i].posts[j].title<<"!" << endl;
                    oStream << "Maximal number of comments is "<<MAX_COMMENTS<<"." << endl;
                    throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
                }}
            catch (Exception_t &exception){
                cout << exception.error_info;
                return 0; }
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
    //execute the command
    int line=0;
    istringstream iStream;
    string command;
    string user1,user2;
    int post_id;
    while(line<n){
        if (content[line].find("trending")!=content[line].npos) {
            int rank_num;
            iStream.str(content[line]);
            iStream >> command >> rank_num;
            trending(rank_num, total_users, user);
            line++;
            iStream.clear();
        }
        if (content[line].find("visit")!=content[line].npos) {
            iStream.str(content[line]);
            iStream >> user1 >> command >> user2;
            visit(user[searchname(user1,total_users,user)],user[searchname(user2,total_users,user)]);
            line++;
            iStream.clear();
        }
        if (content[line].find("follow")!=content[line].npos && content[line].find("unfollow")==content[line].npos) {
            iStream.str(content[line]);
            iStream >> user1 >> command >> user2;
            follow(user[searchname(user1,total_users,user)],user[searchname(user2,total_users,user)]);
            line++;
            iStream.clear();
        }
        if (content[line].find("unfollow")!=content[line].npos) {
            iStream.str(content[line]);
            iStream >> user1 >> command >> user2;
            unfollow(user[searchname(user1,total_users,user)],user[searchname(user2,total_users,user)]);
            line++;
            iStream.clear();
        }
        if (content[line].find("refresh")!=content[line].npos) {
            iStream.str(content[line]);
            iStream >> user1 >> command;
            refresh(user[searchname(user1,total_users,user)]);
            line++;
            iStream.clear();
        }
        if (content[line].find("like")!=content[line].npos && content[line].find("unlike")==content[line].npos) {
            iStream.str(content[line]);
            iStream >> user1 >> command >> user2 >> post_id;
            line++;
            iStream.clear();
            try{
                if(post_id>user[searchname(user2,total_users,user)].num_posts){
                    ostringstream oStream;
                    oStream << ">> like"<<endl;
                    oStream << "Error: "<<user1<<" cannot like post #"<<post_id<<" of "<<user2<<"!" << endl;
                    oStream <<user2<<" does not have post #"<<post_id<<"." << endl;
                    throw Exception_t(INVALID_LOG, oStream.str());
                }}
            catch (Exception_t &exception){
                cout << exception.error_info;
                continue;
            }
            like(user[searchname(user1,total_users,user)],user[searchname(user2,total_users,user)].posts[post_id-1],post_id);
        }
        if (content[line].find("unlike")!=content[line].npos) {
            iStream.str(content[line]);
            iStream >> user1 >> command >> user2 >> post_id;
            line++;
            iStream.clear();
            try{
                if(post_id>user[searchname(user2,total_users,user)].num_posts){
                    ostringstream oStream;
                    oStream << ">> unlike"<<endl;
                    oStream << "Error: "<<user1<<" cannot unlike post #"<<post_id<<" of "<<user2<<"!" << endl;
                    oStream <<user2<<" does not have post #"<<post_id<<"." << endl;
                    throw Exception_t(INVALID_LOG, oStream.str());
                }}
            catch (Exception_t &exception){
                cout << exception.error_info;
                continue;
            }
            unlike(user[searchname(user1,total_users,user)],user[searchname(user2,total_users,user)].posts[post_id-1],post_id);
        }
        if (content[line].find("comment")!=content[line].npos && content[line].find("uncomment")==content[line].npos) {
            string text;
            iStream.str(content[line]);
            iStream >> user1 >> command >> user2 >> post_id;
            line++;
            text=content[line];
            line++;
            iStream.clear();
            try{
                if(post_id>user[searchname(user2,total_users,user)].num_posts){
                    ostringstream oStream;
                    oStream << ">> comment"<<endl;
                    oStream << "Error: "<<user1<<" cannot comment post #"<<post_id<<" of "<<user2<<"!" << endl;
                    oStream <<user2<<" does not have post #"<<post_id<<"." << endl;
                    throw Exception_t(INVALID_LOG, oStream.str());
                }}
            catch (Exception_t &exception){
                cout << exception.error_info;
                continue;
            }
            comment(user[searchname(user1,total_users,user)],user[searchname(user2,total_users,user)].posts[post_id-1],text);
        }

        if (content[line].find("uncomment")!=content[line].npos) {
            int comment_id;
            iStream.str(content[line]);
            iStream >> user1 >> command >> user2 >> post_id >> comment_id;
            line++;
            iStream.clear();
            try{
                if(post_id>user[searchname(user2,total_users,user)].num_posts){
                    ostringstream oStream;
                    oStream << ">> uncomment"<<endl;
                    oStream << "Error: "<<user1<<" cannot uncomment comment #"<<comment_id<<" of "<<"post #"<<post_id<<" posted by "<<user2<<"!" << endl;
                    oStream <<user2<<" does not have post #"<<post_id<<"." << endl;
                    throw Exception_t(INVALID_LOG, oStream.str());
                }}
            catch (Exception_t &exception){
                cout << exception.error_info;
                continue;
            }
            uncomment(user[searchname(user1,total_users,user)],user[searchname(user2,total_users,user)].posts[post_id-1],post_id, comment_id);
        }

        if (content[line].find("post")!=content[line].npos) {
            string title,tags[MAX_TAGS],text;
            int num_tags;
            iStream.str(content[line]);
            iStream >> user1 >> command;
            line++;
            l=0;
            title=content[line];
            line++;
            while(content[line].find_first_of("#")==0){
                tags[l]=content[line].substr(1,content[line].rfind("#")-1);
                line++;l++;
            }
            num_tags=l;
            text=content[line];
            post(user[searchname(user1,total_users,user)],title,tags,num_tags,text);
            line++;
            iStream.clear();
        }
        if (content[line].find("delete")!=content[line].npos) {
            iStream.str(content[line]);
            iStream >> user1 >> command >> post_id;
            line++;
            iStream.clear();
            try{
                if(post_id>user[searchname(user1,total_users,user)].num_posts){
                    ostringstream oStream;
                    oStream << ">> delete"<<endl;
                    oStream << "Error: "<<user1<<" cannot delete post #"<<post_id<<"!" << endl;
                    oStream <<user1<<" does not have post #"<<post_id<<"." << endl;
                    throw Exception_t(INVALID_LOG, oStream.str());
                }}
            catch (Exception_t &exception){
                cout << exception.error_info;
                continue;
            }
            unpost(user[searchname(user1,total_users,user)],post_id);
        }
        if (content[line]==""){line++;}
    }
    return 0;
}
