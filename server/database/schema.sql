CREATE TABLE if not exists usuarios
(
id integer primary key autoincrement,
nombre varchar(25) unique not null,
hashContrasenia varchar(129) not null,
correoElectronico varchar(128) unique not null
);

CREATE TABLE if not exists mensajes
(
id integer primary key autoincrement,
idEmisor integer not null,
idReceptor integer not null,
texto varchar(750) not null,
foreign key (idEmisor) references usuarios (id),
foreign key (idReceptor) references usuarios (id),
check (idEmisor <> idReceptor)
);