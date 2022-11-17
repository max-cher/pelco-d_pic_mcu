def calc_point(p0, p1, x):
    x0 = p0[0]
    x1 = p1[0]
    y0 = p0[1]
    y1 = p1[1]
    if x == x0:
        return y0
    if x == x1:
        return y1
    
    dx = p1[0] - p0[0]
    dy = p1[1] - p0[1]
    if dy == 0:
        return y0
    y = y0 + dy*((x - x0)/dx)
    
    return y


def find_point(M, x):
    for i in range(len(M)-1):
        if x > M[i][0] and x <= M[i+1][0]:
            return(M[i], M[i+1])
    return(M[0], M[1])
