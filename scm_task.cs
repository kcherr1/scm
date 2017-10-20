/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class scm_task : scm_item {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal scm_task(global::System.IntPtr cPtr, bool cMemoryOwn) : base(SCMPINVOKE.scm_task_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(scm_task obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~scm_task() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          SCMPINVOKE.delete_scm_task(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public scm_task() : this(SCMPINVOKE.new_scm_task__SWIG_0(), true) {
  }

  public scm_task(int arg0, long arg1) : this(SCMPINVOKE.new_scm_task__SWIG_1(arg0, arg1), true) {
  }

  public scm_task(int arg0, long arg1, ulong arg2, int arg3, int arg4, int arg5, uint arg6, scm_cache arg7) : this(SCMPINVOKE.new_scm_task__SWIG_2(arg0, arg1, arg2, arg3, arg4, arg5, arg6, scm_cache.getCPtr(arg7)), true) {
  }

  public void make_page(int arg0, int arg1) {
    SCMPINVOKE.scm_task_make_page(swigCPtr, arg0, arg1);
  }

  public bool load_page(string arg0, SWIGTYPE_p_TIFF arg1) {
    bool ret = SCMPINVOKE.scm_task_load_page(swigCPtr, arg0, SWIGTYPE_p_TIFF.getCPtr(arg1));
    return ret;
  }

  public void dump_page() {
    SCMPINVOKE.scm_task_dump_page(swigCPtr);
  }

  public ulong o {
    set {
      SCMPINVOKE.scm_task_o_set(swigCPtr, value);
    } 
    get {
      ulong ret = SCMPINVOKE.scm_task_o_get(swigCPtr);
      return ret;
    } 
  }

  public int n {
    set {
      SCMPINVOKE.scm_task_n_set(swigCPtr, value);
    } 
    get {
      int ret = SCMPINVOKE.scm_task_n_get(swigCPtr);
      return ret;
    } 
  }

  public int c {
    set {
      SCMPINVOKE.scm_task_c_set(swigCPtr, value);
    } 
    get {
      int ret = SCMPINVOKE.scm_task_c_get(swigCPtr);
      return ret;
    } 
  }

  public int b {
    set {
      SCMPINVOKE.scm_task_b_set(swigCPtr, value);
    } 
    get {
      int ret = SCMPINVOKE.scm_task_b_get(swigCPtr);
      return ret;
    } 
  }

  public uint u {
    set {
      SCMPINVOKE.scm_task_u_set(swigCPtr, value);
    } 
    get {
      uint ret = SCMPINVOKE.scm_task_u_get(swigCPtr);
      return ret;
    } 
  }

  public bool d {
    set {
      SCMPINVOKE.scm_task_d_set(swigCPtr, value);
    } 
    get {
      bool ret = SCMPINVOKE.scm_task_d_get(swigCPtr);
      return ret;
    } 
  }

  public SWIGTYPE_p_void p {
    set {
      SCMPINVOKE.scm_task_p_set(swigCPtr, SWIGTYPE_p_void.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = SCMPINVOKE.scm_task_p_get(swigCPtr);
      SWIGTYPE_p_void ret = (cPtr == global::System.IntPtr.Zero) ? null : new SWIGTYPE_p_void(cPtr, false);
      return ret;
    } 
  }

  public scm_cache C {
    set {
      SCMPINVOKE.scm_task_C_set(swigCPtr, scm_cache.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = SCMPINVOKE.scm_task_C_get(swigCPtr);
      scm_cache ret = (cPtr == global::System.IntPtr.Zero) ? null : new scm_cache(cPtr, false);
      return ret;
    } 
  }

}
