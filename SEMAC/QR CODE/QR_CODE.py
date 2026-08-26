import qrcode 
import pandas as pd
import os

def le_data():
    df = pd.read_excel('INSCRIÇÕES SEMAC FINAL.xlsx')
    return df

def gera_qr_code():
    df = le_data()
    pasta_qrcodes_por_email = "qrcodes"
    os.makedirs(pasta_qrcodes_por_email, exist_ok=True)
    for email in df['E-mail']:
        if pd.notna(email):
            img = qrcode.make(str(email))
            img.save(os.path.join(pasta_qrcodes_por_email, f"{email}.png"))
    print("QR Codes gerados com sucesso!")

if __name__ == "__main__":
    gera_qr_code()