/*********************************Copyright (c)*********************************                                      
  *                                            
  ******************************************************************************
  * �ļ����ƣ�24CXX.H
  * ��    ����EEPROMģ��ͷ�ļ�
  * �� �� ��: 
  * ��������:   
  * �� �� ��:             
  * �޸�����:      
  * ��    ��: 
  ******************************************************************************
  * attention
  *
  ******************************************************************************
  */

#ifndef  __24CXX_H__
#define  __24CXX_H__


/**********************ͷ�ļ����ü�������������*********************************/
/*  ������Ҫ��ͷ�ļ�  */


/*  �Ӻ�������        */
unsigned char  EEPROM_Read_Byte(  unsigned char dataaddress );
unsigned char  EEPROM_Read_NByte(  unsigned char *pbuffer,  unsigned char n, unsigned char dataaddress );
unsigned char  EEPROM_Write_Byte(  unsigned char dataaddress, unsigned char wdata );
unsigned char  EEPROM_Write_NByte(unsigned char *pbuffer,  unsigned char n, unsigned char dataaddress );


#endif  
