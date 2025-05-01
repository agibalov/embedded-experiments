import shutil
import os

src = os.path.join("esp32-frontend", "dist")
dst = "data"

if os.path.exists(dst):
    shutil.rmtree(dst)
shutil.copytree(src, dst)
print(f"Copied static files from '{src}' to '{dst}'")
