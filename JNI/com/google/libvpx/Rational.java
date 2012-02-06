// Copyright 2012 Google Inc. All Rights Reserved.
// Author: frkoenig@google.com (Fritz Koenig)
package com.google.libvpx;

/**
 * Holds a rational number
 *
 */
public class Rational {
  private final int num;
  private final int den;

  public Rational() {
    num = 0;
    den = 1;
  }

  public Rational(int num, int den) {
    this.num = num;
    this.den = den;
  }

  public Rational(String num, String den) {
    this.num = Integer.parseInt(num);
    this.den = Integer.parseInt(den);
  }

  public Rational multiply(Rational b) {
    return new Rational(num * b.num(), den * b.den());
  }

  public Rational multiply(int b) {
    return new Rational(num * b, den);
  }

  public int num() {
    return num;
  }

  public int den() {
    return den;
  }

  public String toString() {
    if (den == 1) {
      return new String(num + "");
    } else {
      return new String(num + "/" + den);
    }
  }
}
