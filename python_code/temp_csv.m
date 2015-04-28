m = csvread('/Users/y1275963/consistent-trees/read_tree/test.csv');
x = m(:,3);
y = m(:,4);
z = m(:,5);
rad = m(:,2)/1000;

[x_base,y_base,z_base] = sphere;
hold on;
for index = 1:length(x)
    x_temp = x(index);
    y_temp = y(index);
    z_temp = z(index);
    rad_temp = rad(index);
    
    mesh(x_temp+x_base*rad_temp,y_temp+y_base*rad_temp,z_temp+z_base*rad_temp);
    
end