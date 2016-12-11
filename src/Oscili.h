/////////////////////////////////////////////////////////////////////
// Oscili class: interpolating oscillator
// Copyright (C) 2016-7 V Lazzarini
//
// This software is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3.0 of the License, or (at your option) any later version.
//
/////////////////////////////////////////////////////////////////////
#ifndef _OSCILI_H
#define _OSCILI_H

#include "Oscil.h"

namespace AuLib {
  
  /** Linear interpolation oscillator
   */
  class Oscili : public Oscil {

  public:
    /** Oscili constructor \n\n
	amp - amplitude   \n
	freq - frequency in Hz \n
	phase - init phase (0-1) \n 
	vsize - vector size \n
	sr - sampling rate \n\n
        Uses internal sine wave table
    */
    Oscili(double amp = 0., double freq = 0.,
	  double phase = 0., uint32_t vsize = def_vsize,
	  double sr = def_sr) :
      Oscil(amp,freq,phase,vsize,sr) { };
      
    /** Oscili constructor \n\n
	amp - amplitude \n
	freq - frequency in Hz \n
	ftable - function table \n
	phase - init phase (0-1) \n 
	vsize - vector size \n
	sr - sampling rate \n
    */
    Oscili(double amp, double freq,
	   FuncTable& ftable,
	   double phase = .0,
	   uint32_t vsize = def_vsize,
	   double sr = def_sr) :
      Oscil(amp,freq,ftable,phase,vsize,sr) { };

    /** Process one vector of audio
     */
    virtual void process();

    /** Process one vector of audio
	with amplitude amp
    */
    virtual void process(double amp) {
      m_amp = amp;
      process();
    }

    /** Process one vector of audio
	with amplitude amp and
	frequency freq
    */
    virtual void process(double amp, double freq){
      m_amp = amp;
      m_freq = freq;
      m_incr = m_freq*m_tsize/m_sr;
      process();
    }

    /** Process one vector of audio
	with amplitude and (optional) freq modulation
    */
    virtual void process(const double *amp, const double *freq = NULL){
      m_am = amp;
      m_fm = freq;
      process();
    }

    /** Process one vector of audio
	with amplitude amp 
	and freq modulation
    */
    virtual void process(double amp, const double *freq){
      m_amp = amp;
      m_fm = freq;
      process();
    }

    /** Process one vector of audio
	with amplitude modulation 
	and frequency freq
    */ 
    virtual void process(const double *amp, double freq){
      m_am = amp;
      m_freq = freq;
      m_incr = m_freq*m_tsize/m_sr;
      process();
    }
 
  
  };

}
#endif
