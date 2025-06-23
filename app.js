// Firebase config
const firebaseConfig = {
  apiKey: "AIzaSyCceV4Aj6aa_xcjT4dPCkY6McQdjbWF8wc",
  authDomain: "registro-mecacueva.firebaseapp.com",
  databaseURL: "https://registro-mecacueva-default-rtdb.firebaseio.com",
  projectId: "registro-mecacueva",
  storageBucket: "registro-mecacueva.appspot.com",
  messagingSenderId: "614121047597",
  appId: "1:614121047597:web:a62ed67b9a7baa2ef1daa4"
};
firebase.initializeApp(firebaseConfig);

const auth = firebase.auth();
const db = firebase.database();

const loginBtn = document.getElementById("loginBtn");
const logoutBtn = document.getElementById("logoutBtn");
const email = document.getElementById("email");
const password = document.getElementById("password");
const authMessage = document.getElementById("authMessage");

const authContainer = document.getElementById("auth-container");
const appContainer = document.getElementById("app-container");
const content = document.getElementById("content");

auth.onAuthStateChanged(user => {
  if (user) {
    authContainer.style.display = "none";
    appContainer.style.display = "block";
    loadPersons();
  } else {
    authContainer.style.display = "block";
    appContainer.style.display = "none";
  }
});

loginBtn.onclick = () => {
  auth.signInWithEmailAndPassword(email.value, password.value)
    .then(() => {
      email.value = "";
      password.value = "";
    })
    .catch((error) => {
      authMessage.innerText = error.message;
    });
};

logoutBtn.onclick = () => {
  auth.signOut();
};

// Mostrar personas
const showPersonsBtn = document.getElementById("showPersonsBtn");
showPersonsBtn.onclick = () => loadPersons();

// Mostrar registros
const showLogsBtn = document.getElementById("showLogsBtn");
showLogsBtn.onclick = () => {
  db.ref("/registros_acceso").once("value", snapshot => {
    let html = `<h2>Registros de Acceso</h2><table><tr><th>Hora</th><th>ID Huella</th><th>Nombre</th></tr>`;
    snapshot.forEach(child => {
      const data = child.val();
      const date = new Date(data.timestamp * 1000);
      const timeStr = date.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
      const dateStr = date.toLocaleDateString();
      html += `<tr><td>${dateStr}, ${timeStr}</td><td>${data.id_huella_leida}</td><td>${data.nombre || "-"}</td></tr>`;
    });
    html += `</table>`;
    content.innerHTML = html;
  });
};

function loadPersons() {
  db.ref("/personas").once("value", snapshot => {
    let html = `<h2>Personas Registradas</h2><table><tr><th>ID</th><th>Nombre</th><th>Semestre</th><th>Acciones</th></tr>`;
    snapshot.forEach(child => {
      const data = child.val();
      html += `<tr>
        <td>${data.idHuella}</td>
        <td>${data.nombre}</td>
        <td>${data.semestre}</td>
        <td>
          <button class='edit-button' onclick='editPerson("${child.key}", ${JSON.stringify(data).replace(/"/g, '&quot;')})'>Editar</button>
          <button class='delete-button' onclick='deletePerson("${child.key}")'>Eliminar</button>
        </td></tr>`;
    });
    html += `</table>`;
    content.innerHTML = html;
  });
}

function deletePerson(key) {
  if (confirm("¿Estás seguro de eliminar esta persona?")) {
    db.ref("/personas/" + key).remove().then(loadPersons);
  }
}

function editPerson(key, data) {
  document.getElementById("personKeyInput").value = key;
  document.getElementById("personNameInput").value = data.nombre;
  document.getElementById("personSemesterInput").value = data.semestre;
  document.getElementById("personFingerprintIdInput").value = data.idHuella;
  document.getElementById("personModal").style.display = "flex";
}

document.getElementById("savePersonBtn").onclick = () => {
  const key = document.getElementById("personKeyInput").value;
  const nombre = document.getElementById("personNameInput").value;
  const semestre = document.getElementById("personSemesterInput").value;
  const idHuella = parseInt(document.getElementById("personFingerprintIdInput").value);
  db.ref("/personas/" + key).set({ nombre, semestre, idHuella }).then(() => {
    document.getElementById("personModal").style.display = "none";
    loadPersons();
  });
};

document.querySelectorAll(".close-button").forEach(btn => {
  btn.onclick = () => {
    document.getElementById("personModal").style.display = "none";
  };
});
