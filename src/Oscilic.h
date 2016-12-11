////////////////////////////////////////////////////////////////////
// Oscilic class: cubic interpolating oscillator
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

  /** Cubic interpolation oscillator
   */
  class Oscilic : public Oscil {

  public:
    /** Oscilic constructor \n\n
	amp - amplitude   \n
	freq - frequency in Hz \n
	phase - init phase (0-1) \n 
	vsize - vector size \n
	sr - sampling rate \n\n
	Uses internal sine wave table
    */
    Oscilic(double amp = 0., double freq = 0.,
	    double phase = 0., uint32_t vsize = def_vsize,
	    double sr = def_sr) :
      Oscil(amp,freq,phase,vsize,sr) { };
      
    /** Oscilic constructor \n\n
	amp - amplitude \n
	freq - frequency in Hz \n
	ftable - function table \n
	phase - init phase (0-1) \n 
	vsize - vector size \n
	sr - sampling rate \n
    */
    Oscilic(double amp, double freq,
	    const FuncTable& ftable,
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
    virtual void process(const double* amp, const double* freq = NULL){
      m_am = amp;
      m_fm = freq;
      process();
    }

    /** Process one vector of audio
	with amplitude amp 
	and freq modulation
    */
    virtual void process(double amp, const double* freq){
      m_amp = amp;
      m_fm = freq;
      process();
    }

    /** Process one vector of audio
	with amplitude modulation 
	and frequency freq
    */ 
    virtual void process(const double* amp, double freq){
      m_am = amp;
      m_freq = freq;
      m_incr = m_freq*m_tsize/m_sr;
      process();
    }

    /** Process one vector of audio
	with amplitude modulation from obja
    */ 
    virtual void process(const AudioBase& obja){
      if(obja.vsize() == m_vsize) {
	m_am = obja.output();
        process();
      } else m_error = AULIB_ERROR;
    }

    /** Process one vector of audio
	with amplitude modulation from obja
	and frequency freq
    */ 
    virtual void process(const AudioBase& obja, double freq){
      m_freq = freq;
      m_incr = m_freq*m_tsize/m_sr;
      process(obja);
    }

    /** Process one vector of audio
	with amplitude amp 
	and freq modulation from objf
    */
    virtual void process(double amp, const AudioBase& objf){
      if(objf.vsize() == m_vsize &&
	 objf.nchnls() == 1) {
	m_amp = amp;
	m_fm = objf.output();
        process();
      } else m_error = AULIB_ERROR;
    }

    /** Process one vector of audio
	with amplitude from obja and freq modulation from objf
    */
    virtual void process(const AudioBase& obja, const AudioBase& objf){
      if(obja.vsize() == m_vsize &&
	 objf.vsize() == m_vsize &&
	 obja.nchnls() == 1 &&
	 objf.nchnls() == 1) {
	m_am = obja.output();
	m_fm = objf.output();
        process();
      } else m_error = AULIB_ERROR;
    }
  
  };

  /*! \class Oscilic Oscilic.h AuLib/Oscil.h
   */
}
#endif
