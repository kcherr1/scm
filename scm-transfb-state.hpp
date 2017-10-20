#ifndef SCM_TRANSFB_STATE_HPP
#define SCM_TRANSFB_STATE_HPP

typedef enum _scm_transfb_state {
  TFB_IDLE,
  TFB_CAPTURE_NEXT_FRAME,
  TFB_CAPTURING,
  TFB_PAUSED
}
scm_transfb_state;

#endif
