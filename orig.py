import pygame
from pygame import gfxdraw
import math
import sys
import numpy as np
import cmath

pygame.init()
width, height = 1000, 1000
screen = pygame.display.set_mode((width, height),
                                 pygame.DOUBLEBUF | pygame.RESIZABLE)
clock = pygame.time.Clock()
pygame.display.set_caption("Ray casting")

colors = [(120, 80, 180), (80, 120, 180), (180, 120, 80), (120, 180, 80)]

map = [
    ((2, 0), (1, 0)),
    ((0, 2), (0, 1)),
    ((-2, 0), (-1, 0)),
    ((0, -2), (0, -1))  
      ]


def gen_circle_walls(pos, r, n):
    inc = 2*math.pi/(n + 1)
    l = []
    for t in np.arange(0, 2*math.pi, inc):
        l.append((( pos[0] + r*math.cos(t), pos[1] + r*math.sin(t))
                  ,(pos[0] + r*math.cos(t+inc), pos[1] + r*math.sin(t+inc))))
    return l

def rot_vec(v, a):
    return np.cos(a)*v[0] - np.sin(a)*v[1], np.sin(a)*v[0] + np.cos(a)*v[1]


def vec_cross(v1, v2):
    return (v1[0] * v2[1] - v1[1] * v2[0])


def hypot(v):
    return math.sqrt(v[0]*v[0] + v[1]*v[1])


def sub_vec(v1, v2):
    return (v2[0] - v1[0], v2[1] - v1[1])


def add_vec(v1, v2):
    return (v1[0] + v2[0], v1[1] + v2[1])


def scale_vec_to(v, c):
    t = get_angle((1, 0),v)
    return (c*np.cos(t), c*np.sin(t))


def scale_vec_by(v, c):
    return (v[0] * c, v[1] * c)

def dot(v1, v2):
    return v1[0]*v2[0] + v1[1]*v2[1]

def get_angle(v1, v2):
    if (hypot(v1) and hypot(v2)):
        unit_vector_1 = scale_vec_by(v1, 1 / hypot(v1))
        unit_vector_2 = scale_vec_by(v2, 1 / hypot(v2))
        dot_product = dot(unit_vector_1, unit_vector_2)
        sign = -1 if vec_cross(v1, v2) < 0 else 1
        return sign * np. arccos(dot_product)
    return 0

def blend_colors(base, b, added, a):
    return (
            min(255, int(added[0]*a + base[0]*b)),
            min(255, int(added[1]*a + base[1]*b)),
            min(255, int(added[2]*a + base[2]*b)))

def draw_vec(pos, vec ,scale ,color):
    m = hypot(vec) * scale
    x,y = pos
    a  = get_angle(vec,(1,0))
    mx = np.cos(a)*m*2
    my = np.sin(a)*m*2
    a += 0.5*math.pi
    pointlist = []
    pointlist.append((int(mx + x + np.sin(a)*m),int(my + y - np.cos(a)*m)))
    pointlist.append((int(mx + x + np.sin(a+0.67*math.pi)*(m/3)),int(my + y - np.cos(a+0.67*math.pi)*(m/3))))
    pointlist.append((int(mx + x),int(my + y)))
    pointlist.append((int(mx + x + np.sin(a-0.67*math.pi)*(m/3)),int(my + y - np.cos(a-0.67*math.pi)*(m/3))))
    pygame.draw.line(screen, color, (int(x),int(y)), (int(x+mx),int(y+my)), int(4*scale//m))
    pygame.gfxdraw.filled_polygon(screen, pointlist, color)

def draw_vec_old(x,y,m,a,s,c):
    m *= s
    a *= -1
    mx = np.cos(a)*m*2
    my = np.sin(a)*m*2
    a += 0.5*math.pi
    pointlist = []
    pointlist.append((int(mx + x + np.sin(a)*m),int(my + y - np.cos(a)*m)))
    pointlist.append((int(mx + x + np.sin(a+0.67*math.pi)*(m/3)),int(my + y - np.cos(a+0.67*math.pi)*(m/3))))
    pointlist.append((int(mx + x),int(my + y)))
    pointlist.append((int(mx + x + np.sin(a-0.67*math.pi)*(m/3)),int(my + y - np.cos(a-0.67*math.pi)*(m/3))))
    pygame.draw.line(screen, c, (int(x),int(y)), (int(x+mx),int(y+my)), 2)
    pygame.gfxdraw.filled_polygon(screen, pointlist, c)


def det_cardinals(wall):
    a = get_angle((1,0),sub_vec(wall[0],wall[1]))
    a += math.pi/2
    v = (math.cos(a),math.sin(a))
    ns = dot(v,(0,1))
    we = dot(v,(1,0))
    color_ns = colors[0] if ns > 0 else colors[1]  # n and s
    color_we = colors[2] if we > 0 else colors[3]  # w and e
    return (blend_colors(color_ns, abs(ns), color_we, abs(we)))


def polar_to_cart(v):
    return (v[0]*math.cos(v[1]),v[0]*math.sin(v[1]))

# returns distance to p1
def collision(p1, p2, v1, v2):
    if (vec_cross(v1, v2)):
        scale_v1 = vec_cross(sub_vec(p2, p1), v2)/vec_cross(v1, v2)
        scale_v2 = vec_cross(sub_vec(p2, p1), v1)/vec_cross(v2, v1)
        if (0 < scale_v1 <= 1 and 0 < scale_v2 <= 1):
            return (hypot((v1[0]*scale_v1, v1[1]*scale_v1)))
    return (-1)

class Cam:
    def __init__(self, pos=[0, 0], norm=[0, 1], fov=math.pi/2, far=10):
        self.pos = pos
        self.norm = norm
        self.fov = fov                                              
        self.far = far

    def draw_env(self, cf, cc):
        pygame.draw.rect(screen, cf, pygame.Rect(0, 0, width, height//2))
        pygame.draw.rect(screen, cc, pygame.Rect(0, height//2, width, height))

    def draw_col(self,dist, col, thick, color):
        if (dist > 0):
            scaled = min(height, height/dist)
            pygame.draw.line(screen, color,
                             (int(col), int(height//2+scaled//2)),
                             (int(col), int(height//2-scaled//2)), thick)


    def cast_rays(self,pixel_per_ray):
        a = get_angle(self.norm,(1, 0)) + math.pi/11
        for t in np.arange( a - self.fov/2, a+ self.fov/2, pixel_per_ray*self.fov/width):
            d =[]
            v = (-self.far * math.cos(t),
                 self.far * math.sin(t))
            for w in map:
                c  = collision(self.pos, w[0], v, sub_vec(w[0], w[1]))
                if (c > 0):
                    d.append((c,w))
            if (len(d)):
                self.draw_col(min(d)[0],int((t - a + self.fov/2)*width),pixel_per_ray*2,det_cardinals(min(d)[1]))
            
    def draw_map_rect(self, walls, Pos, size):
        unit = size//10
        pygame.draw.rect(screen, (100,100,100), pygame.Rect(Pos[0]-size,Pos[1]-size,Pos[0]+size,Pos[1]+size))                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
        pygame.draw.circle(screen,(150,50,50),Pos,unit//2)
        for w in walls:
            d1 = scale_vec_by(sub_vec(self.pos, w[0]), unit)
            d2 = scale_vec_by(sub_vec(self.pos, w[1]), unit)
            p1 = Pos[0] + d1[0], Pos[1] - d1[1]
            p2 = Pos[0] + d2[0], Pos[1] - d2[1]
            pygame.draw.line(screen, (130,30,130), p1, p2, 2)
        draw_vec(Pos,self.norm,unit,(100,50,50))

    def draw_map_circle(self, walls, Pos, size):
        unit = size//10
        pygame.draw.circle(screen,(100,100,100), Pos, size)
        for w in walls:
            d1 = sub_vec(self.pos, w[0])
            d2 = sub_vec(self.pos, w[1])
            v1 = hypot(d1)*unit, get_angle((1,0),d1)
            v2 = hypot(d2)*unit, get_angle((1,0),d2)
            if (v1[0] < size or v2[0] < size):
                l1 = min(v1[0],size - 1)
                l2 = min(v2[0],size - 1)
                pygame.draw.line(screen, (130,30,130), 
                             (Pos[0] + l1*math.cos(v1[1]),Pos[1] - l1*math.sin(v1[1]) ), 
                             (Pos[0] + l2*math.cos(v2[1]),Pos[1] - l2*math.sin(v2[1]) )
                             , 2)
        draw_vec(Pos,self.norm,unit,(100,50,50))
        pygame.draw.circle(screen,(150,50,50),Pos,unit//2)
        pygame.draw.circle(screen,(10,10,10), Pos, size, unit//4)

    def draw_map_circle_centered(self, walls, Pos, size):
        unit = size//10
        pygame.draw.circle(screen,(100,100,100), Pos, size)
        for w in walls:
            d1 = sub_vec(self.pos, w[0])
            d2 = sub_vec(self.pos, w[1])
            v1 = hypot(d1)*unit, get_angle((1,0),d1) - get_angle((0,1),self.norm ) 
            v2 = hypot(d2)*unit, get_angle((1,0),d2) - get_angle((0,1),self.norm ) 
            if (v1[0] < size or v2[0] < size):
                l1 = min(v1[0],size - 1)
                l2 = min(v2[0],size - 1)
                pygame.draw.line(screen, (130,30,130), 
                             (Pos[0] + l1*math.cos(v1[1]),Pos[1] - l1*math.sin(v1[1]) ), 
                             (Pos[0] + l2*math.cos(v2[1]),Pos[1] - l2*math.sin(v2[1]) )
                             ,3 )
        draw_vec(Pos,(0,1),unit,(100,50,50))
        pygame.draw.arc(screen,(100,50,50),[Pos[0] - self.far*unit//2, Pos[1] + self.far*unit//2, self.far*unit, self.far*unit ]
                        ,get_angle((1,0),self.norm)-self.fov//2,get_angle((1,0),self.norm)+self.fov//2)
        pygame.draw.circle(screen,(150,50,50),Pos,unit//2)
        pygame.draw.circle(screen,(10,10,10), Pos, size, unit//4)

    def collide(self, walls, size):
        for w in walls:
            v = add_vec(
                sub_vec(self.pos, w[0]),
                scale_vec_by(sub_vec(w[0],w[1]),0.6))
            if (hypot(v) < size):
                self.pos = add_vec(self.pos,
                                    polar_to_cart(
                                    (size - hypot(v),  get_angle((0,1), v) - math.pi*0.5)))

        
# map += gen_circle_walls((0,0),5,50)
cam = Cam(far=20)
while True:
    clock.tick(60)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                sys.exit()
        elif event.type == pygame.VIDEORESIZE:
            width, height = screen.get_size()
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        cam.norm = rot_vec(cam.norm, math.pi/16)
    elif keys[pygame.K_RIGHT]:
        cam.norm = rot_vec(cam.norm, -math.pi/16)
    if keys[pygame.K_w]:
        cam.pos = add_vec(
            cam.pos, scale_vec_to(cam.norm, 0.1))
    elif keys[pygame.K_s]:
        cam.pos = add_vec(
            cam.pos, scale_vec_to(cam.norm, -0.1))
    if keys[pygame.K_a]:
        cam.pos = add_vec(cam.pos,
                          scale_vec_to(     
                              rot_vec(cam.norm, math.pi/2), 0.1))
    elif keys[pygame.K_d]:
        cam.pos = add_vec(cam.pos,
                          scale_vec_to(
                              rot_vec(cam.norm, math.pi/2), -0.1))
    cam.collide(map,0.6)
    cam.draw_env((50, 50, 50), (155, 155, 155))
    cam.cast_rays(4)
    cam.draw_map_circle_centered(map, (width - height//4,height//4),height//4)
    pygame.display.flip()
pygame.quit()