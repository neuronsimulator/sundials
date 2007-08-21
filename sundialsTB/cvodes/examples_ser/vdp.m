function vdp()
%VDP - CVODES example problem (serial, dense)
%   van der Pol problem.

% Radu Serban <radu@llnl.gov>
% Copyright (c) 2005, The Regents of the University of California.
% $Revision: 1.6 $Date: 2007/08/21 17:42:39 $


data.mu = 100.0;

t0 = 0.0;
tf = 300.0;
y0 = [2.0;0.0];

options = CVodeSetOptions('UserData',data,...
                          'RelTol',1.e-8,...
                          'AbsTol',1e-6,...
                          'JacobianFn',@djacfn);
mondata.mode = 'both';
mondata.skip = 20;
options = CVodeSetOptions(options,'MonitorFn',@CVodeMonitor,'MonitorData',mondata);

CVodeInit(@rhsfn, 'BDF', 'Newton', t0, y0, options);

ntout = 50;
dt = (tf-t0)/ntout;
tt = linspace(t0+dt,tf,ntout-1);

[status,t,y] = CVode(tt,'Normal');
  
CVodeFree;

figure;
plot(t,y(1,:),'r',t,y(1,:),'.');

% ===========================================================================

function [yd, flag, new_data] = rhsfn(t, y, data)
% Right-hand side function

mu = data.mu;

yd = [            y(2)
        mu*(1-y(1)^2)*y(2)-y(1) ];

flag = 0;
new_data = [];

return

% ===========================================================================

function [J, flag, new_data] = djacfn(t, y, fy, data)
% Dense Jacobian function (if using Newton)

mu = data.mu;

J = [         0                  1
      -2*mu*y(1)*y(2)-1    mu*(1-y(1)^2) ];

flag = 0;
new_data = [];