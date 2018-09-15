void listAll(const Class* c, string path)  // two-parameter overload
{
    if(path == ""){
        path = c->name();
    }
    else{
        path= path + "=>" + c->name();
    }
    cout<<path<<endl;
    if(c->subclasses().empty()){
        return;
    }
    for(int i = 0; i < c->subclasses().size(); i++){
        listAll(c->subclasses()[i], path);
    }
    
}
