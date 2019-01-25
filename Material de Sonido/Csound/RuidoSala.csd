<CsoundSynthesizer>
<CsOptions>
-W -o SonidoSala.wav
</CsOptions>
<CsInstruments>

sr = 48000
ksmps = 10
nchnls = 1

; EJEMPLO DEL PROFESOR

instr 1
  iamp  = ampdbfs(p4)  ; amplitud de dBFS a PCM
  ifc   = p5  ; frec. corte 
  ifsen = 120 ; frecuencia del tono sinusoidal

  arosa pinkish  iamp                ; ruido rosa
  aseno oscil    iamp/10, ifsen, 100 ; tono sinusoidal
  aout  tone     arosa+aseno, ifc    ; filtro pasa-baja de la suma de componentes
        out      aout
endin

</CsInstruments>
<CsScore>

t 0 60

f 100 0 1024 10 1
; p1   p2   p3   p4   p5  
;ins  ini  dur  amp   fc
;=========================
i 1   0.0  15   -30  180 

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
