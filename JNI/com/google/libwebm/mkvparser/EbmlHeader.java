// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class EbmlHeader extends Common {

  public EbmlHeader() {
    nativePointer = newEBMLHeader();
  }

  public String getDocType() {
    return getDocType(nativePointer);
  }

  public long getDocTypeReadVersion() {
    return getDocTypeReadVersion(nativePointer);
  }

  public long getDocTypeVersion() {
    return getDocTypeVersion(nativePointer);
  }

  public long getMaxIdLength() {
    return getMaxIdLength(nativePointer);
  }

  public long getMaxSizeLength() {
    return getMaxSizeLength(nativePointer);
  }

  public long getReadVersion() {
    return getReadVersion(nativePointer);
  }

  public long getVersion() {
    return getVersion(nativePointer);
  }

  public void init() {
    Init(nativePointer);
  }

  public long parse(IMkvReader mkvReader, long[] position) {
    return Parse(nativePointer, mkvReader.getNativePointer(), position);
  }

  public void setDocType(String docType) {
    setDocType(nativePointer, docType);
  }

  public void setDocTypeReadVersion(long docTypeReadVersion) {
    setDocTypeReadVersion(nativePointer, docTypeReadVersion);
  }

  public void setDocTypeVersion(long docTypeVersion) {
    setDocTypeVersion(nativePointer, docTypeVersion);
  }

  public void setMaxIdLength(long maxIdLength) {
    setMaxIdLength(nativePointer, maxIdLength);
  }

  public void setMaxSizeLength(long maxSizeLength) {
    setMaxSizeLength(nativePointer, maxSizeLength);
  }

  public void setReadVersion(long readVersion) {
    setReadVersion(nativePointer, readVersion);
  }

  public void setVersion(long version) {
    setVersion(nativePointer, version);
  }

  protected EbmlHeader(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteEBMLHeader(nativePointer);
  }

  private native void deleteEBMLHeader(long jEbmlHeader);
  private native String getDocType(long jEbmlHeader);
  private native long getDocTypeReadVersion(long jEbmlHeader);
  private native long getDocTypeVersion(long jEbmlHeader);
  private native long getMaxIdLength(long jEbmlHeader);
  private native long getMaxSizeLength(long jEbmlHeader);
  private native long getReadVersion(long jEbmlHeader);
  private native long getVersion(long jEbmlHeader);
  private native void Init(long jEbmlHeader);
  private native long newEBMLHeader();
  private native long Parse(long jEbmlHeader, long jMkvReader, long[] jPosition);
  private native void setDocType(long jEbmlHeader, String jDocType);
  private native void setDocTypeReadVersion(long jEbmlHeader, long docTypeReadVersion);
  private native void setDocTypeVersion(long jEbmlHeader, long docTypeVersion);
  private native void setMaxIdLength(long jEbmlHeader, long maxIdLength);
  private native void setMaxSizeLength(long jEbmlHeader, long maxSizeLength);
  private native void setReadVersion(long jEbmlHeader, long readVersion);
  private native void setVersion(long jEbmlHeader, long version);
}
