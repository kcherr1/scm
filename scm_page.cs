/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class scm_page : scm_item {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal scm_page(global::System.IntPtr cPtr, bool cMemoryOwn) : base(SCMPINVOKE.scm_page_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(scm_page obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~scm_page() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          SCMPINVOKE.delete_scm_page(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public scm_page() : this(SCMPINVOKE.new_scm_page__SWIG_0(), true) {
  }

  public scm_page(int f, long i) : this(SCMPINVOKE.new_scm_page__SWIG_1(f, i), true) {
  }

  public scm_page(int f, long i, int l) : this(SCMPINVOKE.new_scm_page__SWIG_2(f, i, l), true) {
  }

  public scm_page(int f, long i, int l, int t) : this(SCMPINVOKE.new_scm_page__SWIG_3(f, i, l, t), true) {
  }

  public int l {
    set {
      SCMPINVOKE.scm_page_l_set(swigCPtr, value);
    } 
    get {
      int ret = SCMPINVOKE.scm_page_l_get(swigCPtr);
      return ret;
    } 
  }

  public int t {
    set {
      SCMPINVOKE.scm_page_t_set(swigCPtr, value);
    } 
    get {
      int ret = SCMPINVOKE.scm_page_t_get(swigCPtr);
      return ret;
    } 
  }

}