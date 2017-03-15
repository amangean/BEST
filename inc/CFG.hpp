#ifndef _CFG_HPP_
#define _CFG_HPP_

#include "types.h"
#include <lemon/list_graph.h>
#include <map>

class Inst;
class BB;
class CFG {
  friend class ICFG;
  friend class DFS;
  friend class DT;
  friend class PDT;
  friend class CDG;
  friend class DDG;
  friend class PDG;
  friend class Slicer;

public:
  CFG ();
  
  lemon::ListDigraph::Node            addBB   (BB &);
  lemon::ListDigraph::Arc             addEdge (BB &, BB &);
    std::             vector<BB *>   *bbs     ();
    std::             vector<Inst *> *insts   ();
  static CFG  *Reverse  (const CFG *);
  static CFG  *FromFile (std::string);
  static void  ToFile   (std::string, CFG *);
  static void  ToUPPAAL (std::string, std::string, CFG *, std::vector<Inst *> *);
  
protected:
    std::             string                             m_name;
    std::             string                             m_label;
  
  lemon::             ListDigraph                       *m_graph;
    std::             map<int,lemon::ListDigraph::Node> *m_nodes;
  lemon::ListDigraph::NodeMap<BB *>                     *m_bbs;
  
  lemon::ListDigraph::NodeMap< std::vector<BB *> * >    *m_preds;
  lemon::ListDigraph::NodeMap< std::vector<BB *> * >    *m_succs;
  lemon::ListDigraph::Node                               m_entry;
  lemon::ListDigraph::Node                               m_exit;

private:
  lemon::ListDigraph::Node findByLabel (std::string);
  void findSuccs (std::vector<BB *> &);
  void deadcode_patch ();
  void blr_patch ();
  void print_state (struct state);
};

#endif // _CFG_HPP_
