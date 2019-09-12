#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Node class will hold the information about a node of the tree
Variables of node class :
1. _parent -> pointer to the parent of the nodes
2. _distance -> distance from the origin
3. _level -> level in the hierachy
4. _name -> Name of the node.
*/
class Node {
public:
  Node * _parent;
  int _distance;
  int _level;
  string _name;

  void set_pointer(Node * parent);
  void set_distance (int distance);
  void set_name(string name);
  void set_level(int level);
  int get_distance();
  void print();
};


vector <string *> graph_List; //stores the input state file
vector <Node *> fringe; //fringe to store active nodes under investigation
string GOAL;
int max_num_fringe;
int max_num_expanded;
int max_num_generated;
vector <string> visited;
int is_this_node_visited(Node * current_node)
{
  vector<string>::iterator it;
  it = std::find (visited.begin(), visited.end(), current_node -> _name);
  if (it != visited.end())
  return 0;
  else
  return 1;
}

bool compare_Nodes( Node *n1,  Node *n2)
{
  return n1->_distance > n2->_distance;
}

void Node::print()
{/*
  ostringstream ss;
  ss<<_source<<" "<< _destination<<" " << _distance;
  cout<<ss.str()<<endl;
  */
}
int Node::get_distance()
{
  return _distance;
}
void Node::set_pointer(Node *parent)
{
  _parent = parent;
}
void Node::set_distance(int distance)
{
  _distance = distance;
}

void Node::set_name(string name)
{
  _name = name;
}
void Node::set_level(int level)
{
  _level = level;
}



void add_to_fringe(Node * curr)
{

  fringe.push_back(curr);
  max_num_fringe++;
  max_num_generated++;


}

int expand_node()
{
  if (fringe.empty())
  {
    return -1;
  }
  sort(fringe.begin(), fringe.end(),compare_Nodes);
  Node *expand_node= fringe.back();
  fringe.pop_back();
  max_num_fringe--;
  if (GOAL.compare(expand_node->_name) == 0)
  return 1;
  else if( is_this_node_visited(expand_node))
    return 0;
  else
  {
    string node_name = expand_node->_name;
    int i ;
    while ( i < graph_List.size())
    {
      if(node_name.compare(graph_List[i][0])==0)
      {
        Node * temp = new Node;
        temp->set_name(graph_List[i][1]);
        temp->set_distance(expand_node->_distance + stoi(graph_List[i][2]));
        temp->set_level(expand_node->_level + 1);
        temp->set_pointer(expand_node);
        max_num_expanded++;
        add_to_fringe(temp);
      }
      if(node_name.compare(graph_List[i][1])==0)
      {
        Node * temp = new Node;
        temp->set_name(graph_List[i][0]);
        temp->set_distance(expand_node->_distance + stoi(graph_List[i][2]));
        temp->set_level(expand_node->_level + 1);
        temp->set_pointer(expand_node);
        max_num_expanded++;
        add_to_fringe(temp);

      }
      i++;
    }
  }
  return 0;
}




void uniform_search (char ** argv)
{
  char delim = ' ';
  string input_File_Name = argv[1];
  GOAL = argv[3]; //the node that we are searching for

  //creating the origin node which is the start point for the search.
  Node * origin = new Node;
  origin->set_name(argv[1]);
  origin->set_pointer((Node *) NULL);
  origin->set_distance(0);
  origin->set_level(0);
  visited.push_back(argv[1]);


  add_to_fringe(origin);
  int result;
  do{
      result = expand_node()
  }
  while (result)

  if


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
