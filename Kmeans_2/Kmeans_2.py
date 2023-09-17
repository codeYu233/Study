
import numpy as np
import scipy.io as sio
import matplotlib.pyplot as plt





data=sio.loadmat('Kmeans_2.mat')
data.keys()






A=data['test']
A.shape








A=A/255

plt.imshow(A)
plt.show()
A=A.reshape(-1,3)
A.shape





def find_centroids(X,centros):
    
    idx=[]
    
    for i in range(len(X)):
        dist = np.linalg.norm((X[i]-centros),axis=1)
        id_i=np.argmin(dist)
        idx.append(id_i)
        
    return np.array(idx)





def compute_centros(X,idx,k):
    
    centros=[]
    
    for i in range(k):
        centros_i=np.mean(X[idx==i],axis=0)
        centros.append(centros_i)
        
    return np.array(centros)




def run_kmeans(X,centros,iters):
    
    k=len(centros)
    centros_all=[]
    centros_all.append(centros)
    centros_i=centros
    for i in range(iters):
        idx=find_centroids(X,centros_i)
        centros_i=compute_centros(X,idx,k)
        centros_all.append(centros_i)
        
    return idx,np.array(centros_all)





def init_centros(X,k):
    index=np.random.choice(len(X),k)
    return X[index]





k=16
idx,centros_all=run_kmeans(A,init_centros(A,k=16),iters=20)
centros=centros_all[-1]
im=np.zeros(A.shape)
for i in range(k):
    im[idx==i]=centros[i]
im=im.reshape(642,642,3)
print(im)
plt.imshow(im)
plt.show()

