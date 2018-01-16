/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Presentation;

import Business.BusinessFacade;
import Business.UCInvalida;
import java.util.List;
import java.util.Set;
import javax.swing.JFrame;

/**
 *
 * @author rafae
 */
public class ChangeShiftFrame extends javax.swing.JFrame {

    private static final String NO_SHIFT = "--";
    
    
    private final BusinessFacade bFacade;
    private final String uc;
    private final List<String> shifts;
    
    
    public ChangeShiftFrame(BusinessFacade bFacade, String uc, 
            List<String> shifts) {
        initComponents();
        this.bFacade = bFacade;
        this.uc = uc;
        this.shifts = shifts;
        this.styleComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        shiftLabel = new javax.swing.JLabel();
        changeLabel = new javax.swing.JLabel();
        teoComboBox = new javax.swing.JComboBox<>();
        teoShift = new javax.swing.JLabel();
        jSeparator1 = new javax.swing.JSeparator();
        pShift = new javax.swing.JLabel();
        pComboBox = new javax.swing.JComboBox<>();
        changeButton = new javax.swing.JButton();
        cancelButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jPanel1.setBackground(new java.awt.Color(45, 54, 76));

        shiftLabel.setFont(new java.awt.Font("Verdana", 0, 14)); // NOI18N
        shiftLabel.setForeground(new java.awt.Color(255, 255, 255));
        shiftLabel.setText("Turno");

        changeLabel.setFont(new java.awt.Font("Verdana", 0, 14)); // NOI18N
        changeLabel.setForeground(new java.awt.Color(255, 255, 255));
        changeLabel.setText("Mudar para");

        teoComboBox.setBackground(new java.awt.Color(45, 54, 76));
        teoComboBox.setFont(new java.awt.Font("Verdana", 0, 12)); // NOI18N
        teoComboBox.setForeground(new java.awt.Color(255, 255, 255));
        teoComboBox.setBorder(null);

        teoShift.setFont(new java.awt.Font("SansSerif", 0, 12)); // NOI18N
        teoShift.setForeground(new java.awt.Color(255, 255, 255));
        teoShift.setText("jLabel1");

        jSeparator1.setBackground(new java.awt.Color(88, 144, 255));
        jSeparator1.setForeground(new java.awt.Color(88, 144, 255));
        jSeparator1.setOpaque(true);

        pShift.setFont(new java.awt.Font("Verdana", 0, 12)); // NOI18N
        pShift.setForeground(new java.awt.Color(255, 255, 255));
        pShift.setText("jLabel1");

        pComboBox.setBackground(new java.awt.Color(45, 54, 76));
        pComboBox.setFont(new java.awt.Font("Verdana", 0, 12)); // NOI18N
        pComboBox.setForeground(new java.awt.Color(255, 255, 255));
        pComboBox.setBorder(null);

        changeButton.setBackground(new java.awt.Color(88, 144, 255));
        changeButton.setFont(new java.awt.Font("Verdana", 0, 12)); // NOI18N
        changeButton.setForeground(new java.awt.Color(255, 255, 255));
        changeButton.setText("Trocar");
        changeButton.setContentAreaFilled(false);
        changeButton.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        changeButton.setOpaque(true);
        changeButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                changeButtonMouseClicked(evt);
            }
        });

        cancelButton.setBackground(new java.awt.Color(88, 144, 255));
        cancelButton.setFont(new java.awt.Font("Verdana", 0, 12)); // NOI18N
        cancelButton.setForeground(new java.awt.Color(255, 255, 255));
        cancelButton.setText("Cancelar");
        cancelButton.setContentAreaFilled(false);
        cancelButton.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        cancelButton.setOpaque(true);
        cancelButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                cancelButtonMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(pShift)
                            .addComponent(changeButton)
                            .addComponent(teoShift)))
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(37, 37, 37)
                        .addComponent(shiftLabel)))
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(39, 39, 39)
                        .addComponent(cancelButton)
                        .addContainerGap())
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                                .addComponent(changeLabel)
                                .addGap(37, 37, 37))
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                    .addComponent(pComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(teoComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(44, 44, 44))))))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE, 258, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(changeLabel)
                    .addComponent(shiftLabel))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(teoComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(teoShift))
                .addGap(29, 29, 29)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(pShift)
                    .addComponent(pComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 60, Short.MAX_VALUE)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(changeButton)
                    .addComponent(cancelButton))
                .addGap(34, 34, 34))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void cancelButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_cancelButtonMouseClicked
        this.dispose();
    }//GEN-LAST:event_cancelButtonMouseClicked

    private void changeButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_changeButtonMouseClicked
        String p = (String)pComboBox.getSelectedItem();
        
        if (!p.equals(NO_SHIFT)) {
            boolean b = bFacade.trocarTurno(uc, pShift.getText(), p);

            if (b) {
                SuccessFrame s = new SuccessFrame();
                s.setVisible(true);
            } else {
                QueueMessageFrame q = new QueueMessageFrame();
                q.setVisible(true);
            }
            
            this.dispose();
        }
    }//GEN-LAST:event_changeButtonMouseClicked

    
    private void styleComponents() {
        String teo = "";
        String p = "";
        
        try {
            for (String s : shifts) {
                if (!bFacade.isTurnoPratico(uc, s)) {
                    teo = s;
                } else {
                    p = s;
                }
            }
            
            Set<String> teos = bFacade.getTurnosTeoricosUC(uc);
            Set<String> ps = bFacade.getTurnosPraticosUC(uc);
            
            if (teos.size() <= 1) {
                teoShift.setVisible(false);
                teoComboBox.setVisible(false);
            } else {
                teoShift.setText(teo);
                teoComboBox.addItem(NO_SHIFT);
                
                for (String s : teos) {
                    if (!s.equals(teo)) {
                        teoComboBox.addItem(s);
                    }
                }
            }
            
            pShift.setText(p);
            pComboBox.addItem("--");
            
            for (String s : ps) {
                if (!s.equals(p)) {
                    pComboBox.addItem(s);
                }
            }
        } catch (UCInvalida e) {
            throw new RuntimeException(e);
        }
        
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    }
    
    

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton cancelButton;
    private javax.swing.JButton changeButton;
    private javax.swing.JLabel changeLabel;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JComboBox<String> pComboBox;
    private javax.swing.JLabel pShift;
    private javax.swing.JLabel shiftLabel;
    private javax.swing.JComboBox<String> teoComboBox;
    private javax.swing.JLabel teoShift;
    // End of variables declaration//GEN-END:variables
}
