import hou

def chopnetOutputNode(chopnet):
    """Returns the chopnode inside the given chopnet that currently has its display flag set"""
    for n in chopnet.children():
        if n.isAudioFlagSet():
            return n


def split_cpath(pwd):
    """Process the constraints_path parameter of the given node. Returns both the chopnode and the name of the first track in the constraint"""
    cpath = pwd.evalParm("constraints_path")

    chopnode = None
    trackname = None

    if pwd.node(cpath):
        typename = pwd.node(cpath).type().name()
        if typename == "chopnet":
            chopnode = chopnetOutputNode(pwd.node(cpath))
        elif pwd.node(cpath).type().category().name() == "Chop":
            chopnode = pwd.node(cpath)
        else:
            return chopnode, track
        trackname = chopnode.tracks()[0].name()
    else:       
        split_path = cpath.split("/")
        s = "/".join(split_path[:-1])
        trackname = split_path[-1]
        chopnode = pwd.node(s)
    
    return chopnode, trackname


def get_choptrs(chopnode, startidx, asdict=False):
    """Evaluate the 9 channels on the given chop node starting at the startidx.
    Optionally return the results as a dictionary rather than a list."""
    tracks = [t for t in chopnode.tracks()[startidx:startidx+9]]

    choptrs = [t.eval() for t in tracks]
       
    if asdict:
        choptrs = {
            'translate': hou.Vector3(choptrs[0:3]),
            'rotate': hou.Vector3(choptrs[3:6]),
            'scale': hou.Vector3(choptrs[6:9])
        }
        
    return choptrs


def get_cxform(node):
    """Get the target node's current constraint transform matrix. The constraint does not need to be active, but the constraints_path must be set"""
    
    chopnode, tname = split_cpath(node)

    print(chopnode)
    print(tname)
    
    tnames = tuple(t.name() for t in chopnode.tracks())
    start_idx = tnames.index(tname)
    
    choptrs = get_choptrs(chopnode, start_idx, True)

    return hou.hmath.buildTransform(choptrs)
