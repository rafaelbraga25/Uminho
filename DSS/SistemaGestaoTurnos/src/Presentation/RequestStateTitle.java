/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Presentation;

/**
 *
 * @author rafae
 */
public class RequestStateTitle extends javax.swing.JPanel {

    /**
     * Creates new form RequestStateTitle
     */
    public RequestStateTitle() {
        initComponents();
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
        cuLabel = new javax.swing.JLabel();
        fromLabel = new javax.swing.JLabel();
        toLabel = new javax.swing.JLabel();
        indexLabel = new javax.swing.JLabel();

        jPanel1.setBackground(new java.awt.Color(88, 144, 255));
        jPanel1.setMaximumSize(new java.awt.Dimension(500, 32767));
        jPanel1.setName(""); // NOI18N

        cuLabel.setFont(new java.awt.Font("Verdana", 0, 14)); // NOI18N
        cuLabel.setForeground(new java.awt.Color(255, 255, 255));
        cuLabel.setText("UC");

        fromLabel.setFont(new java.awt.Font("Verdana", 0, 14)); // NOI18N
        fromLabel.setForeground(new java.awt.Color(255, 255, 255));
        fromLabel.setText("De");

        toLabel.setFont(new java.awt.Font("Verdana", 0, 14)); // NOI18N
        toLabel.setForeground(new java.awt.Color(255, 255, 255));
        toLabel.setText("Para");
        toLabel.setHorizontalTextPosition(javax.swing.SwingConstants.LEADING);

        indexLabel.setFont(new java.awt.Font("Verdana", 0, 14)); // NOI18N
        indexLabel.setForeground(new java.awt.Color(255, 255, 255));
        indexLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        indexLabel.setText("Posição");
        indexLabel.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(34, 34, 34)
                .addComponent(cuLabel)
                .addGap(27, 27, 27)
                .addComponent(fromLabel)
                .addGap(34, 34, 34)
                .addComponent(toLabel)
                .addGap(32, 32, 32)
                .addComponent(indexLabel)
                .addContainerGap(269, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(19, 19, 19)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(cuLabel)
                    .addComponent(fromLabel)
                    .addComponent(toLabel)
                    .addComponent(indexLabel))
                .addContainerGap(19, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel cuLabel;
    private javax.swing.JLabel fromLabel;
    private javax.swing.JLabel indexLabel;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JLabel toLabel;
    // End of variables declaration//GEN-END:variables
}
