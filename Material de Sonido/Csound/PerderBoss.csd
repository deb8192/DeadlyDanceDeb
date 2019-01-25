<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
-W -o VencerBoss.wav
;-iadc    ;;;uncomment -iadc if realtime audio input is needed too
; For Non-realtime ouput leave only the line below:
; -o oscil.wav -W ;;; for file output any platform
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 32
nchnls = 2
0dbfs  = 1

instr 1



kamp = .2
kenv linen .2, p3*.25, p3, p3*.25
asig oscil kenv*kamp, cpspch(p5), 4 
 
ach2 delay asig, 0.02
ach3 delay asig, 0.04
ach4 delay asig, 0.06
ach5 delay asig, 0.08

     outs asig+ach2+ach3+ach4+ach5, asig+ach2+ach3+ach4+ach5

endin

instr 2

kamp = .2
kenv linen .2, p3*.125, p3, p3*.5
asig oscil kenv*kamp, cpspch(p5), 4 

ach2 delay asig, 0.02
ach3 delay asig, 0.04
ach4 delay asig, 0.06
ach5 delay asig, 0.08

		   outs asig+ach2+ach3+ach4+ach5, asig+ach2+ach3+ach4+ach5
endin

</CsInstruments>
<CsScore>
f1 0 16384 10 1                                          ; Sine
f2 0 16384 10 1 0.5 0.3 0.25 0.2 0.167 0.14 0.125 .111   ; Sawtooth
f3 0 16384 10 1 0   0.3 0    0.2 0     0.14 0     .111   ; Square
f4 0 16384 10 1 1   1   1    0.7 0.5   0.3  0.1          ; Pulse
;ins 	ini 	dur  tabla frec
;-------------------------------------------------------
i  1 	0  	   .36   4	  6
i  1  .36    .36   4	  6
i  2  .72    2     4	  6
e
</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
