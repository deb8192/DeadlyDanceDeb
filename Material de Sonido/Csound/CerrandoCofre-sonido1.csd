<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
-W -o Golpetazo.wav
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
kret expon 2.4, .12, 2.2
asig oscil kamp, cpspch(kret), 4 
 
kamd = .8
kTime times 

if(kTime < 0.02) then
		kres expon 1000, 0.05, 2
elseif(kTime < 0.04) then
		kres expon 1000, 0.05, 2
elseif(kTime < 0.08) then
		kres expon 800, 0.05, 2
else
		kres expon 40, 0.2, 40
endif

kenv linen .8, .005, .2, .26
asid oscil kenv*kamd, kres,1 
asin oscil kenv*kamd, kres,3 
asiv oscil kenv*kamd, kres,4 

;kre expon 6.4, .4, 4.4 ;para conseguir un efecto distinto cambiar
;kcp =  cpspch(kre) 	  ;frequency

     outs asid+asiv+asig, asid+asiv+asig

endin
</CsInstruments>
<CsScore>
f1 0 16384 10 1                                          ; Sine
f2 0 16384 10 1 0.5 0.3 0.25 0.2 0.167 0.14 0.125 .111   ; Sawtooth
f3 0 16384 10 1 0   0.3 0    0.2 0     0.14 0     .111   ; Square
f4 0 16384 10 1 1   1   1    0.7 0.5   0.3  0.1          ; Pulse
;ins 	ini 	dur  tabla 
;-------------------------------------------------------
i  1 	0  	0.24    4	
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
