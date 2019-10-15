import re

pfnre = r'typedef ([^ ]+) \(VKAPI_PTR \*PFN_([a-zA-Z0-9]+)\)\((.*)\);'
functs = []
instanceFuncts = []
devFuncts = []
maxl = -1
with open("temp/vulkanpfns.hpp") as f:
    content = f.readlines()
    for line in content:
        match = re.match(pfnre, line)
        if match:
            func = {
                "type": match.group(1),
                "name": match.group(2),
                "args":match.group(3)
            };
            maxl = max(len(func["name"]), maxl)
            if "VkInstance " in func["args"] or "VkPhysicalDevice " in func["args"]:
                instanceFuncts.append(func)
            else:
                devFuncts.append(func)

lastos = None
oses = ["Win32", "Xlib", "Xcb", "Wayland", "Mir", "Android"]
def writeosdef(f, func):
    global lastos
    found = False
    for os in oses:
        if os in func["name"]:
            if lastos and lastos != os:
                f.write("#endif\n")
            if not lastos or lastos != os:
                lastos = os
                f.write("#ifdef VK_USE_PLATFORM_{}_KHR\n".format(os.upper()))
            found = True
            break
    if lastos and not found:
        f.write("#endif\n")
        lastos = None

def writefs(f, farr):
    for func in farr:
        writeosdef(f, func)
        spaces = (maxl - len(func["name"])) + 10
        spaces = spaces * " "
        line = "PFN_{}{}{};\n".format(func["name"], spaces, func["name"]);
        f.write(line)
def writeloads(f, farr):
    for func in farr:
        writeosdef(f, func)
        f.write("LOAD({});\n".format(func["name"]))

with open("temp/fpdefs.hpp", "w") as f:
    f.write("//Instance Functions\n")
    writefs(f, instanceFuncts)
    f.write("//Device Functions\n")
    writefs(f, devFuncts)
    f.write("//Instance loaders\n")
    writeloads(f, instanceFuncts)
    f.write("//Device loaders\n")
    writeloads(f, devFuncts)

def writeimpls(f, farr):
    for func in farr:
        writeosdef(f, func)
        f.write("{} impldef_{}({});\n".format(func["type"], func["name"], func["args"]))

typemap = {
"VkBool32": "VK_TRUE",
"VkResult": "VK_SUCCESS",
"PFN_vkVoidFunction": "nullptr",
"void": ""
}

def writeimplscpp(f, farr):
    for func in farr:
        writeosdef(f, func)
        f.write("{} DevaFramework::internal::impldef_{}({})\n".format(func["type"], func["name"], func["args"]))
        f.write("{{\n\tVULKAN_ERR.println(\"Called {} without proper driver PFN\");".format(func["name"]))
        f.write("\n\treturn {};\n}}\n".format(typemap[func["type"]]))


with open("temp/impli.hpp", "w") as f:
    writeimpls(f, instanceFuncts)
with open("temp/impli.cpp", "w") as f:
    writeimplscpp(f, instanceFuncts)


with open("temp/impld.hpp", "w") as f:
    writeimpls(f, devFuncts)
with open("temp/impld.cpp", "w") as f:
    writeimplscpp(f, devFuncts)
