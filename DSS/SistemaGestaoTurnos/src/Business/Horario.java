package Business;

import java.util.Arrays;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rafae
 */
public class Horario {
    private final int diaSemana;
    private final int horaInicio;
    private final int horaFim;
    
    
    public Horario(int diaSemana, int horaInicio, int horaFim) {
        this.diaSemana = diaSemana;
        this.horaInicio = horaInicio;
        this.horaFim = horaFim;
    }
    
    
    public Horario(Horario h) {
        diaSemana = h.getDiaSemana();
        horaInicio = h.getHoraInicio();
        horaFim = h.getHoraFim();
    }
    
    
    public int getDiaSemana() {
        return diaSemana;
    }
    
    
    public int getHoraInicio() {
        return horaInicio;
    }

    
    public int getHoraFim() {
        return horaFim;
    }
    
    
    public boolean colide(Horario h) {
        boolean ret = false;
        
        if (diaSemana == h.getDiaSemana()) {
            int hI = h.getHoraInicio();
            int hF = h.getHoraFim();
            
            if ((hI >= horaInicio && hI < horaFim) ||
                    (hF > horaInicio && hF <= horaFim) ||
                    (hI <= horaInicio && hF >= horaFim)) {
                ret = true;
            }
        }
        
        return ret;
    }
    
    
    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
        }
        
        Horario h = (Horario)o;
        
        return horaInicio == h.getHoraInicio() && horaFim == h.getHoraFim() &&
                diaSemana == h.getDiaSemana();
    }
    
    
    @Override
    public int hashCode() {
        return Arrays.hashCode(new Object[] {
            diaSemana,
            horaInicio,
            horaFim
        });
    }
    
    
    @Override
    public Horario clone() {
        return new Horario(this);
    }
}