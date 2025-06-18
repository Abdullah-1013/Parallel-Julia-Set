import tkinter as tk
from tkinter import messagebox
from PIL import Image
import subprocess
import os

def generate_julia():
    try:
        real = entry_real.get()
        imag = entry_imag.get()

        # Run the compiled C program
        subprocess.run(["julia_openmp.exe", real, imag], check=True)

        # Convert PPM to PNG
        img = Image.open("julia_output.ppm")
        img.save("julia_output.png")

        # Display image in GUI
        img = img.resize((400, 400))
        img_tk = tk.PhotoImage(file="julia_output.png")
        image_label.config(image=img_tk)
        image_label.image = img_tk
        messagebox.showinfo("Success", "Julia set generated and saved as 'julia_output.png'")
    except Exception as e:
        messagebox.showerror("Error", str(e))

# GUI Setup
root = tk.Tk()
root.title("Julia Set Generator")
root.geometry("450x550")
root.configure(bg="orange")

tk.Label(root, text="Real Part:", bg="orange", fg="black", font=("Arial", 12)).pack(pady=5)
entry_real = tk.Entry(root, font=("Arial", 12))
entry_real.pack(pady=5)
entry_real.insert(0, "-0.7")

tk.Label(root, text="Imaginary Part:", bg="orange", fg="black", font=("Arial", 12)).pack(pady=5)
entry_imag = tk.Entry(root, font=("Arial", 12))
entry_imag.pack(pady=5)
entry_imag.insert(0, "0.27015")

tk.Button(root, text="Generate Julia Set", font=("Arial", 14), command=generate_julia).pack(pady=20)

image_label = tk.Label(root)
image_label.pack(pady=10)

root.mainloop()
