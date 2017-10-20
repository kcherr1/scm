/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class scm_sphere : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal scm_sphere(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(scm_sphere obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~scm_sphere() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          SCMPINVOKE.delete_scm_sphere(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public scm_sphere(int arg0, int arg1) : this(SCMPINVOKE.new_scm_sphere(arg0, arg1), true) {
  }

  public void prep(scm_scene arg0, SWIGTYPE_p_double arg1, int arg2, int arg3, int arg4, bool arg5) {
    SCMPINVOKE.scm_sphere_prep(swigCPtr, scm_scene.getCPtr(arg0), SWIGTYPE_p_double.getCPtr(arg1), arg2, arg3, arg4, arg5);
  }

  public void draw(scm_scene arg0, SWIGTYPE_p_double arg1, int arg2, int arg3, int arg4, int arg5) {
    SCMPINVOKE.scm_sphere_draw(swigCPtr, scm_scene.getCPtr(arg0), SWIGTYPE_p_double.getCPtr(arg1), arg2, arg3, arg4, arg5);
  }

  public void set_detail(int arg0) {
    SCMPINVOKE.scm_sphere_set_detail(swigCPtr, arg0);
  }

  public void set_limit(int arg0) {
    SCMPINVOKE.scm_sphere_set_limit(swigCPtr, arg0);
  }

  public int get_detail() {
    int ret = SCMPINVOKE.scm_sphere_get_detail(swigCPtr);
    return ret;
  }

  public int get_limit() {
    int ret = SCMPINVOKE.scm_sphere_get_limit(swigCPtr);
    return ret;
  }

  public scm_transfb transfb {
    set {
      SCMPINVOKE.scm_sphere_transfb_set(swigCPtr, scm_transfb.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = SCMPINVOKE.scm_sphere_transfb_get(swigCPtr);
      scm_transfb ret = (cPtr == global::System.IntPtr.Zero) ? null : new scm_transfb(cPtr, false);
      return ret;
    } 
  }

  public void capture_next_frame() {
    SCMPINVOKE.scm_sphere_capture_next_frame(swigCPtr);
  }

  public int ready_to_capture() {
    int ret = SCMPINVOKE.scm_sphere_ready_to_capture(swigCPtr);
    return ret;
  }

  public void set_num_fb_verts(ulong arg0) {
    SCMPINVOKE.scm_sphere_set_num_fb_verts(swigCPtr, arg0);
  }

  public void set_zoom(double x, double y, double z, double k) {
    SCMPINVOKE.scm_sphere_set_zoom(swigCPtr, x, y, z, k);
  }

}