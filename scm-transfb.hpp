#ifndef SCM_TRANSFB_HPP
#define SCM_TRANSFB_HPP

enum scm_transfb_state {
  TFB_IDLE,
  TFB_CAPTURE_NEXT_FRAME,
  TFB_CAPTURING,
  TFB_PAUSED,
  TFB_COUNT,
};

class scm_transfb {
public:
  static int sizePerVertex;
  static char **vars;
  static int numVars;
  scm_transfb_state state;
  int countVerts;

  scm_transfb();

  void set_num_verts(unsigned long long numverts);

  void count_verts();
  void capture_frame();
  int will_capture_frame();

  void begin();
  void pause();
  void resume();
  void end();
  void add_to_count(int amount);

  static void set_size_per_vertex(int size);
  static void set_num_vars(int numVars);
  static void set_var(int len, char *var);
  int num_data();
  unsigned char* get_data();
  unsigned char  get_data_at(int index);
  void destroy_data();

private:
  unsigned long long numverts;
  unsigned char *data;
  unsigned int vbo;
};

#endif
