Virtual environments

# Virtual environments



## Quick Setup
### Linux
1.Install Python Packages
`sudo apt update`
`sudo apt install python3 python3-dev python3-venv`
2. Install pip
`wget https://bootstratp.pypa.io/get-pip.py`
`sudo python3 get-pip.py`
3. Create Environment
`cd your-project-dir`
`python3 -m venv env`
4. Activate Environment
`source env/bin/activate`
5. Deactivate Environment
`deactivate`

### Windows
1.Install Python + Pip from
`python.org/downloads/windows/`
2. Create Environment
`cd your-project-dir`
`py -m venv env`
3. Activate environment
`.\env\Scripts\activate`
4. Deactivate environment
`deactivate`
