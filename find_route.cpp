#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>

using namespace std;



class Node {
public:
    Node * _parent;
    int _distance;
    string _source;
    string _destination;
    void set_pointer(Node * parent);
    void set_distance (string disatnce);
    void set_source(string source);
    void set_destination(string destination);
     int get_distance();
     void print();
    };
    bool compare_Nodes( Node *n1,  Node *n2);
bool compare_Nodes( Node *n1,  Node *n2){
        return n1->_distance < n2->_distance;
  }


vector <Node *> fringe;
void add_to_fringe(vector <string*> v)
{
  for (int i = 0; i < v.size();i++)
  {
    Node *n = new Node;
    n->set_pointer(n);
    n->set_source(v[i][0]);
    n->set_destination(v[i][1]);
    n->set_distance(v[i][2]);
    fringe.push_back(n);
  }
  sort(fringe.begin(), fringe.end(),compare_Nodes);
  for ( int i = 0; i < fringe.size();i++)
  {
    fringe[i]->print();

  }
}


void Node::print()
{
  ostringstream ss;
  ss<<_source<<" "<< _destination<<" " << _distance;
  cout<<ss.str()<<endl;
}
int Node::get_distance()
{
  return _distance;
}
void Node::set_pointer(Node *parent)
{
  _parent = parent;
}
void Node::set_distance(string distance)
{
  int temp;
  istringstream ss(distance);
  ss>>temp;
  _distance = temp;
}

void Node::set_source(string source)
{
  _source = source;
}
void Node::set_destination(string destination)
{
  _destination =destination;
}

void uniform_search (char ** argv)
{
  char delim = ' ';
  string input_File_Name = argv[1];
  string source = argv[2];
  string destination = argv[3];

  vector <string *> graph_List;

  ifstream myfile (input_File_Name);
  if(!myfile) {
    cout << "Cannot open input file.\n";
    return;
  }

  string temp_Str;
  getline(myfile,temp_Str);
  while((temp_Str.compare("END OF INPUT") != 0) && myfile) {

    int i =0;
    istringstream ss(temp_Str);
    string token;
    string *line = new string[3];
    while(getline(ss, token, delim))
    {
      line[i++] = token;
    }
    graph_List.push_back(line);
    getline(myfile,temp_Str);
  }
  myfile.close();
  add_to_fringe(graph_List);

}


int main(int argc, char** argv)
{
  if (argc <3)
{
    printf("Error!\n" );
}
  else if (argc == 4)
  {
    uniform_search(argv);
  }

}
