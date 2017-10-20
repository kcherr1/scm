/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class scm_set : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal scm_set(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(scm_set obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~scm_set() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          SCMPINVOKE.delete_scm_set(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public bool empty() {
    bool ret = SCMPINVOKE.scm_set_empty(swigCPtr);
    return ret;
  }

  public scm_page search(scm_page arg0, int arg1) {
    scm_page ret = new scm_page(SCMPINVOKE.scm_set_search(swigCPtr, scm_page.getCPtr(arg0), arg1), true);
    if (SCMPINVOKE.SWIGPendingException.Pending) throw SCMPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void insert(scm_page arg0, int arg1) {
    SCMPINVOKE.scm_set_insert(swigCPtr, scm_page.getCPtr(arg0), arg1);
    if (SCMPINVOKE.SWIGPendingException.Pending) throw SCMPINVOKE.SWIGPendingException.Retrieve();
  }

  public void remove(scm_page arg0) {
    SCMPINVOKE.scm_set_remove(swigCPtr, scm_page.getCPtr(arg0));
    if (SCMPINVOKE.SWIGPendingException.Pending) throw SCMPINVOKE.SWIGPendingException.Retrieve();
  }

  public scm_page eject(int arg0, long arg1) {
    scm_page ret = new scm_page(SCMPINVOKE.scm_set_eject(swigCPtr, arg0, arg1), true);
    return ret;
  }

  public scm_set() : this(SCMPINVOKE.new_scm_set(), true) {
  }

}
